#pragma once
#ifndef _ABSTRACTSOLVER_
#define _ABSTRRACTSOLVER_
#include <vector>
#include "grid.h"
#include <iostream>

struct AbstractSolver 
{
	int iters;
	double deltaX, deltaY;
	Grid oldGrid;
	Grid newGrid;
	double deltaT;
	AbstractSolver() {};
	AbstractSolver(int iters_, double deltaX_, double deltaY_, double deltaT_) :iters(iters_), deltaX(deltaX_), deltaY(deltaY_), deltaT(deltaT_) {};
	void solve();
};

#endif