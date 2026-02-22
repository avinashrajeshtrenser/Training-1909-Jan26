#include <sstream>
#include <string>
using namespace std;
#include "FileManager.h"
#include "Delivery.h"
#include "Store.h"
#include "Vehicle.h" 

void FileManager::saveDeliveries(const shared_ptr<vector<Delivery>>& deliveries, const string& fileName)
{
    ofstream file(fileName);
    for (auto deliveryIt = deliveries->begin(); deliveryIt != deliveries->end(); ++deliveryIt)
    {
        int storeId = deliveryIt->getStore() ? deliveryIt->getStore()->getStoreId() : -1;
        int vehicleId = deliveryIt->getVehicle() ? deliveryIt->getVehicle()->getVehicleId() : -1;
        file << deliveryIt->getDeliveryId() << "|"
             << deliveryIt->getDeliveryStatus() << "|"
             << deliveryIt->getDeliveryAddress() << "|"
             << storeId << "|"
             << vehicleId << "\n";
    }
}

void FileManager::loadDeliveries(shared_ptr<vector<Delivery>>& deliveries, const shared_ptr<vector<Store>>& stores, const shared_ptr<vector<Vehicle>>& vehicles, const string& fileName)
{
    ifstream file(fileName);
    if (!file) return;
    deliveries->clear();
    string line;
    string token;
    int deliveryId;
    int storeId;
    int vehicleId;
    string deliveryStatus;
    string deliveryAddress;
    while (getline(file, line))
    {
        stringstream lineStream(line);
        getline(lineStream, token, '|');
        deliveryId = stoi(token);
        getline(lineStream, deliveryStatus, '|');
        getline(lineStream, deliveryAddress, '|');
        getline(lineStream, token, '|');
        storeId = stoi(token);
        getline(lineStream, token, '|');
        vehicleId = stoi(token);
        shared_ptr<Store> storePtr = nullptr;
        shared_ptr<Vehicle> vehiclePtr = nullptr;
        for (auto storeIt = stores->begin(); storeIt != stores->end(); ++storeIt)
        {
            if (storeIt->getStoreId() == storeId)
            {
                storePtr = make_shared<Store>(*storeIt);
                break;
            }
        }
        for (auto vehicleIt = vehicles->begin(); vehicleIt != vehicles->end(); ++vehicleIt)
        {
            if (vehicleIt->getVehicleId() == vehicleId)
            {
                vehiclePtr = make_shared<Vehicle>(*vehicleIt);
                break;
            }
        }
        Delivery delivery(deliveryId, deliveryAddress, storePtr);
        delivery.updateDeliveryStatus(deliveryStatus);
        delivery.assignVehicle(vehiclePtr);
        deliveries->push_back(delivery);
    }
}