#pragma once
#ifndef _GRID_
#define _GRID_
#include <iostream>
#include <vector>
#include <complex>

class Grid 
{
	int x_size, y_size;
	std::vector<std::complex<double>> Field;
public:
	Grid() {};
	Grid(int x_size, int y_size);
	~Grid() {};
	void set_cell_info(int x_coords, int y_coords, double ev);
	double get_cell_info(int x_coords, int y_coords);
private:
	//
};

#endif