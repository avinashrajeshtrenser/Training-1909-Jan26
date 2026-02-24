#pragma once
#include <memory>
#include <vector>
#include <string>
#include "DeliveryItem.h"
#include "Vehicle.h"
#include "Store.h"

enum class DeliveryStatus
{
    PENDING_DISPATCH,
    IN_TRANSIT,
    DELIVERED
};

class Delivery
{
private:
    int m_deliveryId;
    DeliveryStatus m_deliveryStatus;
    std::string m_deliveryAddress;
    std::vector<DeliveryItem> m_items;
    std::shared_ptr<Vehicle> m_vehicle;
    std::shared_ptr<Store> m_store;
public:
    Delivery() : m_deliveryId(0), m_deliveryStatus(DeliveryStatus::PENDING_DISPATCH), m_deliveryAddress(""), m_store(nullptr), m_vehicle(nullptr) {}
    Delivery(int id, const std::string& address, std::shared_ptr<Store> store, std::shared_ptr<Vehicle> vehicle) : m_deliveryId(id), m_deliveryStatus(DeliveryStatus::PENDING_DISPATCH), m_deliveryAddress(address), m_store(store), m_vehicle(vehicle) {}
    int getDeliveryId() const;
    DeliveryStatus getDeliveryStatus() const;
    std::string getDeliveryAddress() const;
    std::vector<DeliveryItem>& getItems();
    const std::vector<DeliveryItem>& getItems() const;
    void updateDeliveryStatus(DeliveryStatus);
    void assignVehicle(std::shared_ptr<Vehicle>);
    std::shared_ptr<Vehicle> getVehicle() const;
    std::shared_ptr<Store> getStore() const;
};
