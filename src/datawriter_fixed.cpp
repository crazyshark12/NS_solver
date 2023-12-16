#include "datawriter_fixed.h"

DataWriter::DataWriter(std::string pathName_) : directory(pathName_)
{
    std::filesystem::path dataDir = directory / "data";
    std::filesystem::remove_all(dataDir);
    std::filesystem::create_directories(dataDir);
}

std::filesystem::path DataWriter::createTimeDirectory(int time)
{
    std::filesystem::path localDir = directory / "data" / std::to_string(time);
    std::filesystem::create_directories(localDir);
    return localDir;
}

void DataWriter::setDelta_h(double dh)
{
    this->dh = dh;
}

void DataWriter::writeData(std::vector<std::vector<Macropars>> data, int iter)
{
    
    std::filesystem::path localDir = createTimeDirectory(iter);
    std::ofstream dens(localDir / "dens.txt",std::ios::out);
    std::ofstream pres(localDir / "pres.txt",std::ios::out);
    std::ofstream velX(localDir / "velX.txt",std::ios::out);
    std::ofstream velY(localDir / "velY.txt",std::ios::out);
    std::ofstream temp(localDir / "temp.txt",std::ios::out);


    for (size_t i = 1; i < data.size() - 1; i++)
    {
        for (size_t j = 1; j < data[i].size() - 1; j++)
        {
            dens << data[i][j].dens << " ";
            pres << data[i][j].pres << " ";
            velX << data[i][j].velX << " ";
            velY << data[i][j].velY << " ";
            temp << data[i][j].temp << " ";
        }
        dens << "\n";
        pres << "\n";
        velX << "\n";
        velY << "\n";
        temp << "\n";
    }

    dens.close();
    pres.close();
    velX.close();
    velY.close();
    temp.close();
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
