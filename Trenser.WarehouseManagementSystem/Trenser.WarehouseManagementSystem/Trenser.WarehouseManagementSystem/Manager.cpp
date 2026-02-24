using namespace std;
#include "Manager.h"

vector<shared_ptr<Vehicle>>& Manager::getAllManagedVehicles()
{
    return m_vehicles;
}

vector<shared_ptr<Store>>& Manager::getAllManagedStores()
{
    return m_stores;
}

vector<shared_ptr<Delivery>>& Manager::getAllDeliveries()
{
    return m_deliveries;
}

void Manager::addStore(const shared_ptr<Store>& store)
{
    m_stores.push_back(store);
}

void Manager::addVehicle(const shared_ptr<Vehicle>& vehicle)
{
    m_vehicles.push_back(vehicle);
}

void Manager::addDelivery(const shared_ptr<Delivery>& delivery)
{
    m_deliveries.push_back(delivery);
}

void Manager::requestDispatch(WarehouseController& controller) 
{
    controller.dispatchProduct();
}

void Manager::viewDeliveries(const WarehouseController& controller) const 
{
    controller.listDeliveries();
}

std::string Manager::getRole() const
{
    return "Manager";
}
