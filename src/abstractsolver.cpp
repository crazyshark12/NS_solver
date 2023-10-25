#include "abstractsolver.h"

AbstractSolver::AbstractSolver(Grid grid_)
{
}

void AbstractSolver::setDelta_h(double dh)
{
    delta_h = dh;
}

void AbstractSolver::setStartCondition(std::vector<macroParam> startParams)
{
    points = startParams;
}

void AbstractSolver::setBorderConditions(double upVelocity_, double upTemp_, double downTemp_)
{
    // Здесь можно установить граничные условия для скорости и температуры
}

void AbstractSolver::setWriter(DataWriter* writer_)
{
    writer_ = writer_;
}

void AbstractSolver::setObserver(Observer* observer_)
{
    observer_ = observer_;
}

void AbstractSolver::writePoints(double i)
{
    // Здесь можно записывать текущие значения макропараметров points[] в папку с названием i
}

void AbstractSolver::prepareSolving()
{
    // Здесь можно выполнить подготовку к решению задачи
}

void AbstractSolver::correctData()
{
    // Здесь можно выполнить дозаполнение полей вектора points значениями скорости звука и параметрами смеси
}

void AbstractSolver::prepareVectorSizes()
{
    // Здесь можно подготовить размеры всех векторов
}

void AbstractSolver::setDt()
{
    // Здесь можно установить временной шаг
}

void AbstractSolver::updatePoints()
{
    // Здесь можно обновлять значения макропараметров в ячейках
}

void AbstractSolver::useBorder()
{
    // Здесь можно применить граничные условия для макропараметров
}

void AbstractSolver::UpdateBorderU()
{
    // Здесь можно обновить значения скорости на границах
}

double AbstractSolver::computeT(macroParam p, std::size_t i)
{
    // Здесь можно вычислить температуру в i-ой ячейке
    return EXIT_SUCCESS;
}

bool AbstractSolver::observerCheck(std::size_t currentIteration)
{
    // Здесь можно проверить условия для наблюдателя
    return EXIT_SUCCESS;
}
