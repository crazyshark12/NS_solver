#include <iostream>
#include "abstractsolver.h"


AbstractSolver::AbstractSolver(int iters_, double deltaX_, double deltaY_, double deltaT_) :iters(iters_), deltaX(deltaX_), deltaY(deltaY_), deltaT(deltaT_) {}

void AbstractSolver::setGridSize(int sizeX, int sizeY)
{
    oldGrid = Grid(sizeX, sizeY);
    newGrid = Grid(sizeX, sizeY);
}

void AbstractSolver::setStartParameters(double density, double velocityX, double velocityY, double temperature)
{
    for (int i = 1; i < oldGrid.sizeY - 1; ++i)
    {
        for (int j = 1; j < oldGrid.sizeX - 1; ++j)
        {
            oldGrid.field[i][j].dens = density;
            oldGrid.field[i][j].velX = velocityX;
            oldGrid.field[i][j].velY = velocityY;
            oldGrid.field[i][j].temp = temperature;
            oldGrid.field[i][j].pres = density * UniversalGasConstant * temperature;
        }
    }
    uptadeBorderCells();
}


void AbstractSolver::uptadeBorderCells()
{
    double Twall = 300;
    for (int i = 0; i < oldGrid.sizeY; ++i)
    {
        if (i == 0)
        {
            for (int j = 1; j < oldGrid.sizeX - 1; ++j)
            {
                oldGrid.field[i][j].dens = oldGrid.field[i + 1][j].dens;
                oldGrid.field[i][j].velX = oldGrid.field[i + 1][j].velX;
                oldGrid.field[i][j].velY = -oldGrid.field[i + 1][j].velY;
                oldGrid.field[i][j].temp = -oldGrid.field[i + 1][j].temp + 2 * Twall;
                oldGrid.field[i][j].pres = oldGrid.field[i][j].dens * UniversalGasConstant * oldGrid.field[i][j].temp;
            }
        }
        else if(i == oldGrid.sizeY)
        {
            for (int j = 1; j < oldGrid.sizeX - 1; ++j)
            {
                oldGrid.field[i][j].dens = oldGrid.field[i - 1][j].dens;
                oldGrid.field[i][j].velX = oldGrid.field[i - 1][j].velX;
                oldGrid.field[i][j].velY = -oldGrid.field[i - 1][j].velY;
                oldGrid.field[i][j].temp = -oldGrid.field[i - 1][j].temp + 2 * Twall;
                oldGrid.field[i][j].pres = oldGrid.field[i][j].dens * UniversalGasConstant * oldGrid.field[i][j].temp;
            }
        }
        else
        {
            for (int j = 0; j < oldGrid.sizeX; ++j)
            {
                if (j == 0)
                {
                    oldGrid.field[i][j].dens = oldGrid.field[i][j + 1].dens;
                    oldGrid.field[i][j].velX = oldGrid.field[i][j + 1].velX;
                    oldGrid.field[i][j].velY = -oldGrid.field[i][j + 1].velY;
                    oldGrid.field[i][j].temp = -oldGrid.field[i][j + 1].temp + 2 * Twall;
                }
                else if (j == oldGrid.sizeX - 1)
                {
                    oldGrid.field[i][j].dens = oldGrid.field[i][j - 1].dens;
                    oldGrid.field[i][j].velX = oldGrid.field[i][j - 1].velX;
                    oldGrid.field[i][j].velY = -oldGrid.field[i][j - 1].velY;
                    oldGrid.field[i][j].temp = -oldGrid.field[i][j - 1].temp + 2 * Twall;
                }
                oldGrid.field[i][j].pres = oldGrid.field[i][j].dens * UniversalGasConstant * oldGrid.field[i][j].temp;
            }
        }
    }
}

void AbstractSolver::solve()
{
    double alpha = 0.05;
    double phi = 0;
    double nu = 0.01;

    int iteration = 0;
    while (iters > iteration)
    {
        // pressure
        for (int i = 1; i < oldGrid.sizeY - 1; ++i)
        {
            for (int j = 1; j < oldGrid.sizeX - 1; ++j)
            {
                double F_x = 0;
                double F_y = 0;
                //density
                double densCurt = oldGrid.field[i][j].dens;
                double dr = oldGrid.field[i][j + 1].dens;
                double dl = oldGrid.field[i][j - 1].dens;
                double du = oldGrid.field[i - 1][j].dens;
                double dd = oldGrid.field[i + 1][j].dens;

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


                newGrid.field[i][j].dens = ((dr * velXr - dl * velXl) / (2 * deltaX) + (dd * velYd - du * velYu) / (2 * deltaY));
                newGrid.field[i][j].dens *= deltaT;
                newGrid.field[i][j].dens = oldGrid.field[i][j].dens - newGrid.field[i][j].dens;

                //velocityX

                newGrid.field[i][j].velX = F_x - ((pr - pl) / (2 * deltaX)) / densCurt - ((velXr - velXl) / (2 * deltaX) + (velYd - velYu) / (2 * deltaY)) * velXCurt;
                newGrid.field[i][j].velX += nu * (((velXr - velXCurt) / deltaX - (velXCurt - velXl) / deltaX) / deltaX + ((velXd - velXCurt) / deltaY - (velXCurt - velXu) / deltaY) / deltaY);
                newGrid.field[i][j].velX *= deltaT;
                newGrid.field[i][j].velX += velXCurt;

                //velocityY

                newGrid.field[i][j].velY = F_y - ((pd - pu) / (2 * deltaY)) / densCurt - ((velXr - velXl) / (2 * deltaX) + (velYd - velYu) / (2 * deltaY)) * velYCurt;
                newGrid.field[i][j].velY += nu * (((velYr - velYCurt) / deltaX - (velYCurt - velYl) / deltaX) / deltaX + ((velYd - velYCurt) / deltaY - (velYCurt - velYu) / deltaY) / deltaY);
                newGrid.field[i][j].velY *= deltaT;
                newGrid.field[i][j].velY += velYCurt;

                //temperature
                double tl = oldGrid.field[i][j - 1].temp;
                double tr = oldGrid.field[i][j + 1].temp;
                double tu = oldGrid.field[i - 1][j].temp;
                double td = oldGrid.field[i + 1][j].temp;
                double tCurt = oldGrid.field[i][j].temp;

                newGrid.field[i][j].temp = -((velXCurt * (tr - tl)) / (2 * deltaX) + (velYCurt * (td - tu)) / (2 * deltaY));
                newGrid.field[i][j].temp += alpha * (tr - 2*tCurt + tl) / (pow( deltaX, 2));
                newGrid.field[i][j].temp += alpha * (td - 2*tCurt + tu) / (pow( deltaY, 2));
                newGrid.field[i][j].temp += phi;
                newGrid.field[i][j].temp *= deltaT;
                newGrid.field[i][j].temp += tCurt;

                // пересчет давления с помощью уравнения состояния
                newGrid.field[i][j].pres = newGrid.field[i][j].dens * UniversalGasConstant * newGrid.field[i][j].temp;
            }
        }
        iteration++;
        oldGrid = newGrid;
        uptadeBorderCells();
    }

}


void AbstractSolver::meteorite(int xCoords_, int yCoords_, int index_, double value_)
{
    switch(index_)
    {
        case 1:
            oldGrid.field[xCoords_][yCoords_].dens = value_;
            break;
        case 2:
            oldGrid.field[xCoords_][yCoords_].pres = value_;
            break;
        case 3:
            oldGrid.field[xCoords_][yCoords_].temp = value_;
            break;
    }
}
