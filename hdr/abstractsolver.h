#pragma once

#include <vector>
#include <list>
#include <mutex>
#include <string.h>
#include "grid.h"

struct macroParam
{
    double pressure;
    double velocity;
    double temperature;
    double density;
};


struct Matrix
{
    private:
        int line;
        int column;
        std::vector<std::vector<double>> matrix;


    public:
        Matrix(int line, int column){};
};

class Observer
{
    public:
        bool checkCondition(const macroParam& macroparam)
            {
                return false;
            }
};

class DataWriter
{
    public:
        void writeData(const macroParam& macroparam)
        {
        }
};


class AbstractSolver
{
    private:
        void writePoints(double i);
        virtual void prepareSolving();
        virtual void correctData();
        virtual void prepareVectorSizes();
        void setDt();
        void updatePoints();
        void useBorder();
        void UpdateBorderU();
        double computeT(macroParam p, std::size_t i);
        bool observerCheck(std::size_t currentIteration);

        Grid grid;
        std::vector<macroParam> points;
        double delta_h = 0;
        Matrix timeSolving;
        bool isWriteData = false;
        bool isObserverWatching = false;
        int watcherIteration = 1;
        bool isContinue = false;

    public:
        AbstractSolver(Grid grid_);
        virtual void solve() = 0;
        virtual void solveContinue();
        void setDelta_h(double dh);
        void setStartCondition(std::vector<macroParam> startParams);
        void setBorderConditions(double upVelocity_, double upTemp_, double downTemp_);
        void setWriter(DataWriter* writer_);
        void setObserver(Observer* observer_);
};
