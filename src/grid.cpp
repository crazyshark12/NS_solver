#include <iostream>
#include <grid.h>
#include <vector>

Grid::Grid(int source_x, int source_y) :
	sizeX(source_x), sizeY(source_y)
{
	field.resize(sizeX, std::vector<Macropars>(sizeY));
}

