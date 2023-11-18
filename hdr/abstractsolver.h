#pragma once
#ifndef _ABSTRACTSOLVER_
#define _ABSTRRACTSOLVER_
#include <vector>
#include "grid.h"
#include <iostream>

const double UniversalGasConstant = 8.3144598;

struct AbstractSolver
{
	int iters;
	double deltaX, deltaY;
	Grid oldGrid;
	Grid newGrid;
	double deltaT;
	AbstractSolver() {};
	AbstractSolver(int iters_, double deltaX_, double deltaY_, double deltaT_);
	void setGridSize(int sizeX, int sizeY);
	void setStartParameters(double density, double velocityX, double velocityY, double temperature);
	void uptadeBorderCells();
	void solve();
};

#endif