#include <iostream>
#include <grid.h>

Grid::Grid(int source_x, int source_y) 
{
	x_coords = source_x;
	y_coords = source_y;
}


Grid
Grid::get_cell_info(const Grid& source) 
{
	int tmpx, tmpy;
	float *i = primal_grid[tmpx][tmpy];
	return i;
}
