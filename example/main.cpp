#include "abstractsolver.h"
#include "datawriter_fixed.h"
#include <iostream>

int main()
{
	std::cout << "Bruh";
    AbstractSolver solver(100000, 1, 1, 0.00001);
    solver.setGridSize(100, 100);
    solver.setStartParameters(1000, 0, 0, 300);
	solver.solve();

	return EXIT_SUCCESS;

}
