#pragma once
#ifndef _ABSTRACTSOLVER_
#define _ABSTRRACTSOLVER_
#include <string>
#include <iostream>

class AbstractSolver 
{
	std::string value;
	int x_coords, y_coords;
public:
	AbstractSolver() {};
	AbstractSolver(std::string);
	AbstractSolver(int, int);
	AbstractSolver(const AbstractSolver& source);
	AbstractSolver Nubble(const AbstractSolver&);
};

#endif