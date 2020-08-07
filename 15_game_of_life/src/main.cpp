#include "cell.h"
int main()
{
	int i, ticks = 0;
	std::cout << "Write number of ticks here: " << std::endl;
	std::cin >> ticks;
	Cells matrix(20, 20);
	i = matrix.DrawShape(matrix.BLOCK, 1, 1);
	i = matrix.DrawShape(matrix.BOAT, 4, 4);
	i = matrix.DrawShape(matrix.BLINKER, 8, 8);
	i = matrix.DrawShape(matrix.BEACON, 10, 10);
	i = matrix.DrawShape(matrix.GLIDER, 16, 16);

	for (int i = 0; i < ticks; i++)
	{
		matrix.calculate_new_state();
		matrix.update_state();
		matrix.print_state();
	}

	matrix.print_state();

	return 0;
}
