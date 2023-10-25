#pragma once
#include <vector>

struct Grid
{
    private:
        int sizeX;
        int sizeY;
        //хз дабл или инт использовать чтоб отметить разницу между расстояниями, но я решил дабл
        double deltaX;
        double deltaY;
    public:
        int getSizeX() const;
        int getSizeY() const;
};
