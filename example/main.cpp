#include "abstractsolver.h"
#include "datawriter_fixed.h"
#include <iostream>

int main()
{
	std::cout << "Bruh";
    AbstractSolver solver(10000000, 1, 1, 1e-6);
    solver.setGridSize(100, 100);
    solver.setStartParameters(1.2, 0, 0, 300);
	solver.solve();

	return EXIT_SUCCESS;

}
