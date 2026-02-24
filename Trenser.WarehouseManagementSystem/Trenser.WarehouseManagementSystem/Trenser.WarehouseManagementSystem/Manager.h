#pragma once
#include <vector>
#include <memory>
#include "User.h"
#include "Delivery.h"
#include "Vehicle.h"
#include "Store.h"
#include "WarehouseController.h"

class Manager : public User
{
private:
    std::vector<std::shared_ptr<Delivery>> m_deliveries;
    std::vector<std::shared_ptr<Vehicle>> m_vehicles;
    std::vector<std::shared_ptr<Store>> m_stores;
public:
    Manager() : User(), m_deliveries(), m_vehicles(), m_stores() {}
    Manager(int userId, const std::string& userName, const std::string& password)
        : User(userId, userName, password), m_deliveries(), m_vehicles(), m_stores() {}
    std::vector<std::shared_ptr<Vehicle>>& getAllManagedVehicles();
    std::vector<std::shared_ptr<Store>>& getAllManagedStores();
    std::vector<std::shared_ptr<Delivery>>& getAllDeliveries();
    void addStore(const std::shared_ptr<Store>& store);
    void addVehicle(const std::shared_ptr<Vehicle>& vehicle);
    void addDelivery(const std::shared_ptr<Delivery>& delivery);
    void requestDispatch(WarehouseController& controller);
    void viewDeliveries(const WarehouseController& controller) const;
    std::string getRole() const override;
};
