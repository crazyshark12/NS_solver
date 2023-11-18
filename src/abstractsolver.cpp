#include <iostream>
#include "abstractsolver.h"


void AbstractSolver::solve()
{
	double alpha = 0;
	double phi = 0;
	double rho = 1000;
	double nu = 0;

	while (iters > 0)
	{
		Grid ersatzGrid;
		// pressure
		for (int i = 1; i < sizeof(oldGrid.field) - 1; ++i)
		{
			for (int j = 1; j < sizeof(oldGrid.field[0]) - 1; ++j)
			{
				double F_x = 0;
				double F_y = 0;
				//density
				double dr = oldGrid.field[i][j + 1].dens;
				double dl = oldGrid.field[i][j - 1].dens;
				double du = oldGrid.field[i - 1][j].dens;
				double dd = oldGrid.field[i + 1][j].dens;
				double velX_ = oldGrid.field[i][j + 1].velX;
				double velY_ = oldGrid.field[i + 1][j].velY;

				ersatzGrid.field[i][j].pres = ((dr * velX_ - dl * velX_) / (2 * deltaX) + (dd * velY_ - du * velY_) / (2 * deltaY));
				ersatzGrid.field[i][j].pres *= deltaT;
				ersatzGrid.field[i][j].pres = oldGrid.field[i][j].pres - ersatzGrid.field[i][j].pres;

				//velocityX
				double velXCurt = oldGrid.field[i][j].velX;
				double velXl = oldGrid.field[i][j - 1].velX;
				double velXr = oldGrid.field[i][j + 1].velX;
				double velXd = oldGrid.field[i + 1][j].velX;
				double velXu = oldGrid.field[i - 1][j].velX;

				double velYCurt = oldGrid.field[i][j].velY;
				double velYl = oldGrid.field[i][j - 1].velY;
				double velYr = oldGrid.field[i][j + 1].velY;
				double velYu = oldGrid.field[i - 1][j].velY;
				double velYd = oldGrid.field[i + 1][j].velY;

				double pr = oldGrid.field[i][j + 1].pres;
				double pl = oldGrid.field[i][j - 1].pres;
				double pu = oldGrid.field[i - 1][j].pres;
				double pd = oldGrid.field[i + 1][j].pres;

				ersatzGrid.field[i][j].velX = F_x - ((pr - pl) / (2 * deltaX)) / rho - ((velXr - velXl) / (2 * deltaX) + (velYd - velYu) / (2 * deltaY)) * velXCurt;
				ersatzGrid.field[i][j].velX += nu * (((velXr - velXCurt)/deltaX-(velXCurt - velXl)/deltaX)/deltaX + ((velXd - velXCurt)/deltaY-(velXCurt - velXu)/deltaY)/deltaY);
				ersatzGrid.field[i][j].velX *= deltaT; 
				ersatzGrid.field[i][j].velX += velXCurt;

				//velocityY

				ersatzGrid.field[i][j].velX = F_x - ((pd - pu) / (2 * deltaY)) / rho - ((velXr - velXl) / (2 * deltaX) + (velYd - velYu) / (2 * deltaY)) * velYCurt;
				ersatzGrid.field[i][j].velX += nu * (((velYr - velYCurt) / deltaX - (velYCurt - velYl) / deltaX) / deltaX + ((velYd - velYCurt) / deltaY - (velYCurt - velYu) / deltaY) / deltaY);
				ersatzGrid.field[i][j].velX *= deltaT;
				ersatzGrid.field[i][j].velX += velXCurt;

				ersatzGrid.field[i][j].velY;

				//temperature
				double tl = oldGrid.field[i][j - 1].temp;
				double tr = oldGrid.field[i][j + 1].temp;
				double tu = oldGrid.field[i - 1][j].temp;
				double td = oldGrid.field[i + 1][j].temp;
				double tCurt = oldGrid.field[i][j].temp;

				ersatzGrid.field[i][j].temp = -((velX_ * (tr - tl)) / (2 * deltaX) + (velY_ * (td - tu)) / (2 * deltaY));
				ersatzGrid.field[i][j].temp += alpha * ((((tr - tCurt) / deltaX) - ((tCurt - tl) / deltaX)) / deltaX + (((td - tCurt / deltaY))));
				ersatzGrid.field[i][j].temp += alpha * ((((tCurt - tu) / deltaY)) / deltaY);
				ersatzGrid.field[i][j].temp += phi;
				ersatzGrid.field[i][j].temp *= deltaT;
				ersatzGrid.field[i][j].temp += tCurt;
			}
		}
		oldGrid = ersatzGrid;
	}
	newGrid = oldGrid;

}
