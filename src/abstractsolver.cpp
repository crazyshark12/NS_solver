#include <iostream>
#include "abstractsolver.h"


void AbstractSolver::solve()
{
	double alpha = 0;
	double phi = 0;
	while (iters > 0)
	{
		Grid ersatzGrid;
		// pressure
		for (int i = 1; i < sizeof(oldGrid.field) - 1; ++i)
		{
			for (int j = 1; j < sizeof(oldGrid.field[0]) - 1; ++j)
			{
				//pressure
				ersatzGrid.field[i][j].pres = oldGrid.field[i][j].pres - deltaT * ((oldGrid.field[i][j + 1].pres * oldGrid.field[i][j + 1].velX - oldGrid.field[i][j - 1].pres * oldGrid.field[i][j - 1].velX) / (2 * deltaX) + (oldGrid.field[i + 1][j].pres * oldGrid.field[i + 1][j].velY - oldGrid.field[i - 1][j].pres * oldGrid.field[i - 1][j].velY) / (2 * deltaY));

				//velocityX

				//velocityY

				//temperature
				//double tl = oldGrid.field[i][j - 1].temp;

				ersatzGrid.field[i][j].temp = -((oldGrid.field[i][j].velX * (oldGrid.field[i][j + 1].temp - oldGrid.field[i][j - 1].temp)) / (2 * deltaX) + (oldGrid.field[i][j].velY * (oldGrid.field[i + 1][j].temp - oldGrid.field[i - 1][j].temp)) / (2 * deltaY));
				ersatzGrid.field[i][j].temp += alpha * ((((oldGrid.field[i][j + 1].temp - oldGrid.field[i][j].temp) / deltaX) - ((oldGrid.field[i][j].temp - oldGrid.field[i][j - 1].temp) / deltaX)) / deltaX + (((oldGrid.field[i + 1][j].temp - oldGrid.field[i][j].temp) / deltaY)));
				ersatzGrid.field[i][j].temp += alpha * ((((oldGrid.field[i][j].temp - oldGrid.field[i - 1][j].temp) / deltaY)) / deltaY);
				ersatzGrid.field[i][j].temp += phi;
				ersatzGrid.field[i][j].temp *= deltaT;
				ersatzGrid.field[i][j].temp += oldGrid.field[i][j].temp;
			}
		}
		oldGrid = ersatzGrid;
	}
	newGrid = oldGrid;

}
