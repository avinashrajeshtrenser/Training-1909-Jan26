#pragma once
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include "Delivery.h"
#include "Store.h"
#include "Vehicle.h"

class FileManager
{
public:
    template<typename T>
    void saveVector(const std::shared_ptr<std::vector<T>>& vec, const std::string& fileName)
    {
        std::ofstream out(fileName);
        for (auto& obj : *vec)
            out << obj.serialize() << "\n";
    }
    template<typename T>
    void loadVector(std::shared_ptr<std::vector<T>>& vec, const std::string& fileName)
    {
        std::ifstream in(fileName);
        if (!in) return;
        vec->clear();
        std::string line;
        while (std::getline(in, line))
            vec->push_back(T::deserialize(line));
    }
    void saveDeliveries(const std::shared_ptr<std::vector<Delivery>>& deliveries, const std::string& fileName);
    void loadDeliveries(std::shared_ptr<std::vector<Delivery>>& deliveries,
        const std::shared_ptr<std::vector<Store>>& stores,
        const std::shared_ptr<std::vector<Vehicle>>& vehicles,
        const std::string& fileName);
};