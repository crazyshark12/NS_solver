#include "datawriter_fixed.h"

DataWriter::DataWriter(std::string pathName_) : directory(pathName_)
{
    std::filesystem::path dataDir = directory / "data";
    std::filesystem::remove_all(dataDir);
    std::filesystem::create_directories(dataDir);
}

std::filesystem::path DataWriter::createTimeDirectory(double time)
{
    std::filesystem::path localDir = directory / "data" / std::to_string(time);
    std::filesystem::create_directories(localDir);
    return localDir;
}

void DataWriter::setDelta_h(double dh)
{
    this->dh = dh;
}

void DataWriter::writeData(std::vector<Macropars> data, double time)
{
    
    std::filesystem::path localDir = createTimeDirectory(time);
    std::ofstream dens(localDir / "dens.txt");
    std::ofstream pres(localDir / "pres.txt");
    std::ofstream velX(localDir / "velX.txt");
    std::ofstream velY(localDir / "velY.txt");
    std::ofstream temp(localDir / "temp.txt");

    for (size_t i = 0; i < data.size(); i++) 
    {
        double h = dh * i; 
        for (size_t j = 0; j < 10; j++) 
        {
            dens << data[i].dens << " ";
        }
        dens << "\n";

        for (size_t j = 0; j < 10; j++)
        {
            pres << data[i].pres << " ";
        }
        pres << "\n";

        for (size_t j = 0; j < 10; j++)
        {
            velX << data[i].velX << " ";
        }
        velX << "\n";

        for (size_t j = 0; j < 10; j++)
        {
            velY << data[i].velY << " ";
        }
        velY << "\n";

        for (size_t j = 0; j < 10; j++)
        {
            temp << data[i].temp << " ";
        }
        temp << "\n";
    }
}

void DataReader::getPoints(std::vector<Macropars>& points)
{
    points.clear();
    for (size_t i = 0; i < points.size(); ++i)
    {
        Macropars tmp;
        tmp.dens = points[i].dens;
        tmp.pres = points[i].pres;
        tmp.temp = points[i].temp;
        tmp.velX = points[i].velX;
        tmp.velY = points[i].velY;
        points.push_back(tmp);
    }
    return;
}

bool DataReader::fillDataVector(std::vector<double>& data, std::string dataFileName)
{
    std::ifstream file(pathName + dataFileName);

    if (!file.is_open())
    {
        std::cout << "WARNING: no" << dataFileName << " file to read" << std::endl;
        return 0;
    }

    double h;
    double value;

    while (file >> h >> value)
    {
        data.push_back(value);
    }

    file.close();

    return 1;
}

bool DataReader::read()
{
    if (!fillDataVector(dens_, "/dens.txt") || !fillDataVector(pres_, "/pres.txt")
        || !fillDataVector(temp_, "/temp.txt") || !fillDataVector(velX_, "/velX.txt")
        || !fillDataVector(velY_, "/velY.txt"))
    {
        return 0;
    }
    return 1;
}