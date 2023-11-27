#include "abstractsolver.h"
#include "datawrite.h"
#include <iostream>

int main()
{
    std::cout << "Starting simulation..." << std::endl;

    AbstractSolver solver(1000, 2, 2, 5);
    DataWriter writer("D:/NS_solver");

    solver.setGridSize(1000, 1000);

    double density = 1.0;
    double velocityX = 0.1;
    double velocityY = 0.1;
    double temperature = 300.0;

    solver.setStartParameters(density, velocityX, velocityY, temperature);

    writer.setDelta_h(1.0);

    for (int i = 1; i <= 1000; ++i)
    {
        solver.solve();
        std::vector<Macropars> allCellsData;
        for (int i = 0; i < solver.newGrid.sizeY; ++i) {
            for (int j = 0; j < solver.newGrid.sizeX; ++j)
            {
                allCellsData.push_back(solver.newGrid.field[i][j]);
            }
        }
        writer.writeData(allCellsData, 5 * i); // Сохранение всех ячеек вместо одной
    }

    std::cout << "Simulation completed." << std::endl;

    return EXIT_SUCCESS;
}
