#pragma once
#include <memory>
#include <vector>
#include <string>
#include "DeliveryItem.h"
#include "Vehicle.h"
#include "Store.h"

class Delivery
{
private:
    int m_deliveryId;
    std::string m_deliveryStatus;
    std::string m_deliveryAddress;
    std::vector<DeliveryItem> m_items;
    std::shared_ptr<Vehicle> m_vehicle;
    std::shared_ptr<Store> m_store;
public:
    Delivery() : m_deliveryId(0), m_deliveryStatus("Pending"), m_deliveryAddress(""), m_store(nullptr), m_vehicle(nullptr) {}
    Delivery(int id, const std::string& address, std::shared_ptr<Store> store, std::shared_ptr<Vehicle> vehicle) : m_deliveryId(id), m_deliveryStatus("Dispatched"), m_deliveryAddress(address), m_store(store), m_vehicle(vehicle) {}
    int getDeliveryId() const;
    std::string getDeliveryStatus() const;
    std::string getDeliveryAddress() const;
    std::vector<DeliveryItem>& getItems();
    const std::vector<DeliveryItem>& getItems() const;
    void updateDeliveryStatus(const std::string& status);
    void assignVehicle(std::shared_ptr<Vehicle> vehicle);
    std::shared_ptr<Vehicle> getVehicle() const;
    std::shared_ptr<Store> getStore() const;
};