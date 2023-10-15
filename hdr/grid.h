#pragma once
#ifndef _GRID_
#define _GRID_
#include <iostream>

class Grid 
{
	int x_coords, y_coords;
	float primal_grid[10][10][4]{ 0 };
public:
	Grid() {};
	Grid(int, int);
	Grid(float*);
	Grid(const Grid& source);
	~Grid() {};
	Grid get_cell_info(const Grid&);
private:
	//
};

#endif