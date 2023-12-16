#pragma once
#ifndef _GRID_
#define _GRID_
#include "macropars.h"
#include <iostream>
#include <vector>

struct Grid
{
	int sizeX, sizeY;
	std::vector<std::vector<Macropars>> field;

	Grid() {};
	Grid(int x_size, int y_size);
};

#endif
