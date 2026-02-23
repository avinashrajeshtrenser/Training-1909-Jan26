#include "FileManager.h"

void FileManager::saveDeliveries(const std::vector<Delivery>& deliveries, const std::string& fileName)
{
    std::ofstream file(fileName);
    for (std::vector<Delivery>::const_iterator it = deliveries.begin(); it != deliveries.end(); ++it)
    {
        int storeId = -1;
        int vehicleId = -1;
        if (it->getStore())
        {
            storeId = it->getStore()->getStoreId();
        }
        if (it->getVehicle())
        {
            vehicleId = it->getVehicle()->getVehicleId();
        }
        file << it->getDeliveryId() << "|" << it->getDeliveryStatus() << "|" << it->getDeliveryAddress() << "|" << storeId << "|" << vehicleId << "\n";
    }
}

void FileManager::loadDeliveries(std::vector<Delivery>& deliveries, const std::vector<std::shared_ptr<Store>>& stores, const std::vector<std::shared_ptr<Vehicle>>& vehicles, const std::string& fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        return;
    }
    deliveries.clear();
    std::string line;
    std::string token;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        int deliveryId;
        std::string status;
        std::string address;
        int storeId;
        int vehicleId;
        std::getline(ss, token, '|');
        deliveryId = std::stoi(token);
        std::getline(ss, status, '|');
        std::getline(ss, address, '|');
        std::getline(ss, token, '|');
        storeId = std::stoi(token);
        std::getline(ss, token, '|');
        vehicleId = std::stoi(token);
        std::shared_ptr<Store> store = nullptr;
        std::shared_ptr<Vehicle> vehicle = nullptr;
        for (std::vector<std::shared_ptr<Store>>::const_iterator storeIt = stores.begin(); storeIt != stores.end(); ++storeIt)
        {
            if ((*storeIt)->getStoreId() == storeId)
            {
                store = *storeIt;
                break;
            }
        }
        for (std::vector<std::shared_ptr<Vehicle>>::const_iterator vehicleIt = vehicles.begin(); vehicleIt != vehicles.end(); ++vehicleIt)
        {
            if ((*vehicleIt)->getVehicleId() == vehicleId)
            {
                vehicle = *vehicleIt;
                break;
            }
        }
        Delivery delivery(deliveryId, address, store, vehicle);
        delivery.updateDeliveryStatus(status);
        deliveries.push_back(delivery);
    }
}