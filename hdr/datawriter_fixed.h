#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "abstractsolver.h"

struct DataWriter
{

    DataWriter(std::string pathName);
    std::filesystem::path createTimeDirectory(double time);
    void writeData(std::vector<Macropars> data, double time);
    void setDelta_h(double dh);

private:
    double dh = 1;
    std::filesystem::path directory;
};

struct DataReader
{
    DataReader(std::string pathName) : pathName(pathName) {};
    bool read();
    void getPoints(std::vector<Macropars>& points);

private:
    bool fillDataVector(std::vector<double>& data, std::string dataFileName);
    std::vector<double> dens_, pres_, velX_, velY_, temp_;
    std::vector<Macropars> points;
    std::string pathName;
    double dh = 1;
};