#include "abstractsolver.h"
#include <iostream>

int main() 
{
	std::cout << "Bruh";
    AbstractSolver solver(5, 2, 2, 0.01);
    solver.setGridSize(10,10);
    solver.setStartParameters(1,0,0,300);
    solver.solve();
	return EXIT_SUCCESS;
}
