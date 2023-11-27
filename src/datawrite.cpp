#include "datawrite.h"

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


void DataWriter::writeData(std::vector<Macropars> data, double time)
{
    std::filesystem::path localDir = createTimeDirectory(time);
    std::ofstream dens(localDir/"dens.txt"), pres(localDir/"pres.txt"), velX(localDir/"velX.txt"), velY(localDir/"velY.txt"), temp(localDir/"temp.txt");

    for(size_t i = 0; i < data.size(); i++) {
        double h = dh * i;
        dens << h << " " << data[i].dens << '\n';
        pres << h << " " << data[i].pres << '\n';
        velX << h << " " << data[i].velX << '\n';
        velY << h << " " << data[i].velY << '\n';
        temp << h << " " << data[i].temp << '\n';
    }
}


bool DataReader::fillDataVector(std::vector<double> &data, std::string dataFileName)
{
    std::ifstream file(pathName + dataFileName);

    if (!file.is_open())
    {
        std::cout<<"WARNING: no" << dataFileName <<" file to read"<<std::endl;
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
    if (!fillDataVector(dens_, "/dens.txt") || !fillDataVector(pres_,"/pres.txt")
        || !fillDataVector(temp_,"/temp.txt") || !fillDataVector(velX_,"/velX.txt")
        || !fillDataVector(velY_,"/velY.txt"))
    {
        return 0;
    }
    return 1;
}
