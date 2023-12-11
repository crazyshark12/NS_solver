#include "abstractsolver.h"
#include "datawriter_fixed.h"
#include <iostream>

int main()
{
	std::cout << "Bruh";
	AbstractSolver solver(30, 1, 1, 0.00001);
	solver.setGridSize(10, 10);
	solver.setStartParameters(1000, 0, 0, 20);
	solver.solve();

	return EXIT_SUCCESS;

}