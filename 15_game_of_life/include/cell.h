#pragma once
#include <iostream>
#include <vector>
class Cells
{
private:
	int x_lenght, y_width;
	std::vector <std::vector<bool>> current_state, new_state;
	typedef struct cell
	{
		long int x_coord;
		long int y_coord;
	}cell;
	const cell Shapes[5][6] = { { {0, 0}, {1,0},{0,1},{1, 1} }, // Block
							{{0,0}, {1,0}, {0, 1}, {2, 1},{1,2}}, // boat
							{{0, 0}, {1, 0}, {2, 0} }, //Blinker
							{ {0,0}, {1,0}, {0, 1},{3,2}, {3,3}, {2,3} }, //beacon
							{ {1, 0},{1, 0}, {2, 1},{0,2}, {1, 2}, {2, 2} } }; //glider
	
public:
	typedef	enum shapes
	{
		BLOCK = 0,
		BOAT,
		BLINKER,
		BEACON,
		GLIDER,
	}shapes;

	Cells(int x_lenght, int y_width);
	void calculate_new_state(void);
	void update_state(void);
	int DrawShape(shapes shape,long int x, long int y);
	void print_state(void);
	
};