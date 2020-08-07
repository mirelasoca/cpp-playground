#include "cell.h"

Cells::Cells(int x_lenght, int y_width): x_lenght(x_lenght), y_width(y_width)
{
	for (int y = 0; y < y_width; y++)
	{
		std::vector<bool> v_bool;
		for (int x = 0; x < x_lenght; x++)
		{
			v_bool.emplace_back(false);
		
		}
		current_state.emplace_back(v_bool);
		new_state.emplace_back(v_bool);
	}
}

 void Cells::calculate_new_state(void)
{
	for (int y = 0; y < y_width; y++)
	{
		for (int x = 0; x < x_lenght; x++)
		{
			int alive_neighbours = 0;
			cell neighbours[8] = { {x - 1, y - 1},{x, y - 1},{x + 1, y - 1}, {x - 1, y}, {x + 1, y}, {x - 1, y + 1},{x, y + 1},{x + 1, y + 1} };
			for (cell neighbour : neighbours)
			{
				if (neighbour.x_coord >= 0 && neighbour.y_coord >= 0 && neighbour.y_coord < y_width && neighbour.x_coord <x_lenght)
				{
					if (current_state[neighbour.y_coord][neighbour.x_coord])
						alive_neighbours++;
				}
			}

			if (current_state[y][x])
			{
				new_state[y][x] = (alive_neighbours < 2 || alive_neighbours>3) ? false : true;
			}
			else
			{
				new_state[y][x] = (alive_neighbours == 3) ? true : false;
			}
		}
	}
}

 void Cells::update_state(void)
 {
	 for (int y = 0; y < y_width; y++)
	 {
		 for (int x = 0; x < x_lenght; x++)
		 {
			 current_state[y][x] = new_state[y][x];
		 }
	 }
 }

 int Cells::DrawShape(shapes shape, long int x, long int y)
 {
	 if (x > x_lenght || y > y_width || x < 0)
	 {
		 std::cout << " Error: coordinates out of range" << std::endl;
		 return 1;
	 }
	 for (cell write_cell : Shapes[shape])
	 {
		 if (x + write_cell.x_coord < x_lenght && y + write_cell.y_coord < y_width && x + write_cell.x_coord >= 0 && y + write_cell.y_coord >= 0)
			 current_state[y + write_cell.y_coord][x + write_cell.x_coord] = true;
	 }
	 
	 return 0;
 }

 void Cells::print_state(void)
 {
	 for (int y = 0; y < y_width; y++)
	 {
		 for (int x = 0; x < x_lenght; x++)
		 {
			 if (current_state[y][x])
				 std::cout << "o";
			 else
				 std::cout << "-";
		 }
		 std::cout << std::endl;
	 }
	 std::cout << std::endl;
 }

