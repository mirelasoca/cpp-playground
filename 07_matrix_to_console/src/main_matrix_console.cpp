#include <iostream>
#include <string>
#include <vector>

/**
	Define a simple matrix.
*/
class Matrix
{
private:
	size_t column_count;
	size_t line_count;
	std::vector<std::vector<char>> matrix;

	// TODO: store the data
	// hints: you can use std::string, std::vectors + string, char**, vector<vector<char>>, etc
public:

	Matrix(size_t numColumnsX, size_t numLinesY)
		// TODO: add functionality
	{
		// TODO: add functionality
		column_count = numColumnsX;
		line_count = numLinesY;
		std::vector<char> v_char(column_count);
		for (int i = 0; i < column_count; i++)
			v_char.push_back('0');
		for (int i = 0; i < line_count; i++)
			matrix.push_back(v_char);
		
		
	}

	// Set an entire line
	void setLine(size_t line_number, const std::string& data)
	{
		std::vector<char> v_char;
		if (line_number >= line_count)
			std::cout << "Line number exceeds number of lines" << std::endl;
		if (data.size() > column_count)
			std::cout << "Data line too long" << std::endl;
		else
		{
			for (char x : data)
			{
				v_char.push_back(x);
				//std::cout << x;
			}
			//std::cout << std::endl;
;
			matrix[line_number] = v_char;

		}
	}

	//OPTIONAL
	//char getCellXY(size_t x, size_t y, char cell_content)
	//{
	//	// TODO: add functionality
	//	return 0;
	//}

	/**
		Sets the cell content for a specific cell identified by its coordinates (X and Y)
		@param x The horizontal coordinate of the cell to set. Index starts at zer0.
		@param y The vertical coordinate of the cell to set. Index starts at zer0.
		@param cell_content A cell char to set.

		E.g.
		 X axis: 0 -------- ... -------> Width
		 Y axis
		 0       0,0  1,0                W-1, 0
		 |       0,1  1,1                     
		 |       0,2                      
		 .                             
		 .                             
		 .                             
		 |       0, H-1     ...          W-1, H-1           
		 V

		 Height
	*/
	void setCellXY(size_t x, size_t y, char cell_content)
	{
		// TODO: add functionality
		if (x >= column_count)
			std::cout << " Error: Number of collum exceeds max number of collums" << std::endl;
		if (y >= line_count)
			std::cout << "Error Number of line exceeds max number of lines" << std::endl;
		else
		{
			matrix[y][x] = cell_content;

		}
		
	}

	void print()
	{
		// print all lines and columns
		// TODO: add
		int y, x = 0;
		for (y = 0; y < line_count; y++)
		{
			for (x = 0; x < column_count; x++)
				std::cout << matrix[y][x];
			std::cout << std::endl;
		}
			


	}
};

int main()
{
	// Create a matrix with the width of 20 and height of 10.
	Matrix matrix(20, 10);

	matrix.setLine(0, "X-----X----X-----XX-");
	matrix.setLine(1, "--X-----------------");
	matrix.setLine(2, "-----X--------------");
	matrix.setLine(3, "--------X-----------");
	matrix.setLine(4, "-----------X--------");
	matrix.setLine(5, "--------------X-----");
	matrix.setLine(6, "-----------------X--");
	matrix.setLine(7, "-------------------X");
	matrix.setLine(8, "------------------X-");
	matrix.setLine(9, "-----------------X--");

	matrix.print();
	std::cout << std::endl;
	// Would print
/*
X-----X----X-----XX-
--X-----------------
-----X--------------
--------X-----------
-----------X--------
--------------X-----
-----------------X--
-------------------X
------------------X-
-----------------X--
*/
	matrix.setCellXY(2, 1, '-');
	matrix.print();
	std::cout << std::endl;
	// Would print
/*
X-----X----X-----XX-
--------------------
-----X--------------
--------X-----------
-----------X--------
--------------X-----
-----------------X--
-------------------X
------------------X-
-----------------X--
*/

	matrix.setCellXY(3, 7, 'O');
	matrix.print();
	std::cout << std::endl;
/*
X-----X----X-----XX-
--------------------
-----X--------------
--------X-----------
-----------X--------
--------------X-----
-----------------X--
---O---------------X
------------------X-
-----------------X--
*/

	// This should silently fail (not trigger an error): cell Y=11 invalid due to limited height.
	matrix.setCellXY(3, 11, 'O');
	return 0;
}