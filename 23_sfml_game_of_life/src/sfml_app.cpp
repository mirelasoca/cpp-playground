#include "sfml_app.h"
#include "cell.h"
#include <iostream>
#include <thread>


SfmlApp::SfmlApp(
	std::pair<unsigned int, unsigned int> window_size
)
	: window_({ window_size.first, window_size.second }, "My window")
{

}

SfmlApp::~SfmlApp()
{
}

std::string getMessageForActiveStatus(bool active)
{
	if (active)
	{
		return "Simulation is ACTIVE. Press <SPACE> to toggle the simulation. Press <ESC> to exit.";
	}

	return "Simulation is PAUSED. Press <SPACE> to toggle the simulation. Press <ESC> to exit.";
}

void SfmlApp::init()
{
	readFromIniFile();
	//this->living_cell_color_ = sf::Color(40, 160, 20);
	//this->dead_cell_color_ = sf::Color(25, 23, 21);

	if (font_.loadFromFile("../../data/OpenSans-Regular.ttf"))
	{
		gui_text_.setFont(font_);
		gui_text_.setString(getMessageForActiveStatus(true));
		gui_text_.move(10, 2);
		gui_text_.setCharacterSize(24);
		gui_text_.setOutlineColor(sf::Color::White);
	}
	else
	{
		// error...cannot render GUI
	}

	// Note: you can also override the window size after it is initialized.
	// This could be useful to allow changing the resolution and the world size after the initialization
	// but is not really a priority for this exercise.
	//this->window.setSize(sf::Vector2u(1200, 600));

	// Initialize the vertices
	size_t max_width = static_cast<size_t>(window_.getView().getSize().x);
	size_t max_height = static_cast<size_t>(window_.getView().getSize().y);

	// Store the world size for later use.
	world_size_.first = max_width / cell_size_.first - 1;
	world_size_.second = max_height / cell_size_.second - 1;
	Init_matrix(world_size_.first, world_size_.second);
	DrawShape(BEACON, 10, 10);
	DrawShape(BOAT, 50, 50);
	DrawShape(BLOCK, 70, 50);
	DrawShape(BLINKER, 80, 60);
	

	// Initialize the world map with vertices.
	for (size_t cell_y = 0; cell_y < max_height / cell_size_.first - 1; cell_y++)
	{
		for (size_t cell_x = 0; cell_x < max_width / cell_size_.second - 1; cell_x++)
		{
			this->addVertexQuad(cell_x, cell_y, cell_size_.first, cell_size_.second);
		}
	}
}

void SfmlApp::run()
{
	unsigned time_elapsed_since_update = 0;
	bool simulation_active(true);
	// TODO: it would be nice to make this configurable in the future.
	

	// run the program as long as the window is open
	while (window_.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window_.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
			{
				window_.close();
			}

			// quick close via the ESC key.
			if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window_.close();
					return;
				}
			}

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					// Toggle simulation
					simulation_active = !simulation_active;
					gui_text_.setString(getMessageForActiveStatus(simulation_active));
				}
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Button::Left)
				{
					size_t view_width = static_cast<size_t>(window_.getView().getSize().x);
					size_t view_height = static_cast<size_t>(window_.getView().getSize().y);
					size_t win_width = static_cast<size_t>(window_.getSize().x);
					size_t win_height = static_cast<size_t>(window_.getSize().y);

					unsigned clicked_cell_x = event.mouseButton.x * view_width / (cell_size_.first * win_width);
					unsigned clicked_cell_y = event.mouseButton.y * view_height / (cell_size_.second * win_height);

					// TODO: maybe update a world matrix?
					current_state[clicked_cell_y][clicked_cell_x] = true;
				
					setCellColor(clicked_cell_x, clicked_cell_y, living_cell_color_);
				}
			}
		}

		if (time_elapsed_since_update > duration_in_millis_between_updates)
		{
			updateWorld();
			time_elapsed_since_update -= duration_in_millis_between_updates;
		}

		// clear the window with black color
		window_.clear(sf::Color::Black);

		render();

		// end the current frame
		window_.display();

		// don't consume too many cpu cycles
		std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(10));
		if (simulation_active)
		{
			time_elapsed_since_update += 10;
		}
	}
}

void SfmlApp::setCellColor(unsigned cell_x, unsigned cell_y, sf::Color color)
{
	auto index = (cell_y * this->world_size_.first + cell_x) * 4;
	if (index >= cell_vertices_.size())
	{
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		cell_vertices_[index + i].color = color;
	}
}

void SfmlApp::addVertexQuad(unsigned cell_x, unsigned cell_y, unsigned width, unsigned height)
{
	sf::Vertex topLeft;
	sf::Vertex topRight;
	sf::Vertex bottomLeft;
	sf::Vertex bottomRight;

	float pixel_x = static_cast<float>(cell_x * width);
	float pixel_y = static_cast<float>(cell_y * height);

	topLeft.position = { pixel_x,			 pixel_y };
	topRight.position = { pixel_x + width,   pixel_y };
	bottomLeft.position = { pixel_x,           pixel_y + height };
	bottomRight.position = { pixel_x + width,   pixel_y + height };

	topLeft.color = dead_cell_color_;
	topRight.color = dead_cell_color_;
	bottomLeft.color = dead_cell_color_;
	bottomRight.color = dead_cell_color_;

	cell_vertices_.push_back(topLeft);
	cell_vertices_.push_back(bottomLeft);
	cell_vertices_.push_back(bottomRight);
	cell_vertices_.push_back(topRight);
}

void SfmlApp::render()
{
	// draw everything here...
	window_.draw(cell_vertices_.data(), cell_vertices_.size(), sf::Quads);

	// Add any GUI info.
	window_.draw(gui_text_);
}

void SfmlApp::updateWorld()
{
	// TODO: feel free to add function arguments as deemed necessary.
	for (unsigned int cell_y = 0; cell_y < world_size_.second; cell_y++)
	{
		for (unsigned int cell_x = 0; cell_x < world_size_.first; cell_x++)
		{
			if (current_state[cell_y][cell_x])
			{
				setCellColor(cell_x, cell_y, living_cell_color_);
			}
			else
			{
				setCellColor(cell_x, cell_y,dead_cell_color_);
			}
		}
		calculate_new_state();
		update_state();
	}
	//setCellColor(rand() % world_size_.first, rand() % world_size_.second, living_cell_color_);
}
void SfmlApp:: readFromIniFile(void)
{
	
	// TODO: BEGIN read the file -------------------------------------
	CSimpleIniA ini;
	const char* filename = "../../data/gol_data.ini";
	enum SI_Error rc = ini.LoadFile(filename);
	if (rc < 0)
	{
		std::cout << "error loading file code is " << rc << std::endl;
	};
	cell_size_.first = atoi(ini.GetValue("world", "cell_size.x"));
	cell_size_.second = atoi(ini.GetValue("world", "cell_size.y"));
	living_cell_color_ = sf::Color(atoi(ini.GetValue("livingColor", "color.x")), atoi(ini.GetValue("livingColor", "color.y")), atoi(ini.GetValue("livingColor", "color.z")));
	dead_cell_color_ = sf::Color(atoi(ini.GetValue("deadColor", "color.x")), atoi(ini.GetValue("deadColor", "color.y")), atoi(ini.GetValue("deadColor", "color.z")));
	//window_ = new sf::RenderWindow ({ atoi(ini.GetValue("window", "windowsize.first")), atoi(ini.GetValue("window", "windowsize.second")) }, "MyWindow" );
	duration_in_millis_between_updates = atoi(ini.GetValue("speed", "millis"));
}