#include <iostream>
#include <sstream>
#include <abstractsolver.h>

AbstractSolver::AbstractSolver(std::string source_value) 
{
	value = source_value;
}

AbstractSolver::AbstractSolver(int source_x, int source_y)
{
	x_coords = source_x;
	y_coords = source_y;
}

AbstractSolver
AbstractSolver::Nubble(const AbstractSolver& source) 
{
	int x = x_coords * source.x_coords;
	int y = y_coords * source.y_coords;
	std::string value = value * source.value;
	if (value == "Temp")
	{

	}
	else if (value == "Dens")
	{

	}
	else if (value == "Velo")
	{

	}
	else 
	{

	}

}