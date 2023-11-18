#include "abstractsolver.h"
#include <iostream>

int main() 
{
	std::cout << "Bruh";
	AbstractSolver solver(5, 2, 2, 5);
    solver.setGridSize(10,10);
    solver.setStartParameters();
    solver.solve();
    //solver.solve();
}
