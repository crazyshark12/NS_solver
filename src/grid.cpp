#include <iostream>
#include <grid.h>
#include <vector>

Grid::Grid(int source_x, int source_y) :
	x_size(source_x), y_size(source_y)
{
	Field.resize(x_size, std::vector<double>(y_size, 0));
}


Grid

Grid::set_cell_info(int x_coords, int y_coords, double ev)
{
	Field[x_coords][y_coords] = ev;
}


double Grid::get_cell_info(int x_coords, int y_coords)
{
	return Field[x_coords][y_coords];
}