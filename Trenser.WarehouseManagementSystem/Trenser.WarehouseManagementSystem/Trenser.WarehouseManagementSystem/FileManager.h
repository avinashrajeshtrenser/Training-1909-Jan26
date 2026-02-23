#pragma once
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Delivery.h"
#include "Store.h"
#include "Vehicle.h"

class FileManager
{
public:
    template<typename T>
    void saveVector(const std::vector<std::shared_ptr<T>>& vectors, const std::string& fileName);
    template<typename T>
    void loadVector(std::vector<std::shared_ptr<T>>& vectors, const std::string& fileName);
    void saveDeliveries(const std::vector<Delivery>& deliveries, const std::string& fileName);
    void loadDeliveries(std::vector<Delivery>& deliveries, const std::vector<std::shared_ptr<Store>>& stores, const std::vector<std::shared_ptr<Vehicle>>& vehicles, const std::string& fileName);
};

template<typename T>
inline void FileManager::saveVector(const std::vector<std::shared_ptr<T>>& vectors, const std::string& fileName)
{
    std::ofstream out(fileName);
    for (typename std::vector<std::shared_ptr<T>>::const_iterator it = vectors.begin(); it != vectors.end(); ++it)
    {
        out << (*it)->serialize() << "\n";
    }
}

template<typename T>
inline void FileManager::loadVector(std::vector<std::shared_ptr<T>>& vectors, const std::string& fileName)
{
    std::ifstream in(fileName);
    if (!in)
    {
        return;
    }
    vectors.clear();
    std::string line;
    while (std::getline(in, line))
    {
        vectors.push_back(std::make_shared<T>(T::deserialize(line)));
    }
}