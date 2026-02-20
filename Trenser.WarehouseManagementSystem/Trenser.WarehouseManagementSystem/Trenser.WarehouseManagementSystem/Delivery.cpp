#include "Delivery.h"

int Delivery::getDeliveryId() const 
{ 
    return m_deliveryId;
}
std::string Delivery::getDeliveryStatus() const
{ 
    return m_deliveryStatus; 
}
std::string Delivery::getDeliveryAddress() const 
{
    return m_deliveryAddress; 
}
std::vector<DeliveryItem>& Delivery::getItems()
{
    return m_items;
}
void Delivery::updateDeliveryStatus(const std::string& status)
{
    m_deliveryStatus = status;
}
void Delivery::assignVehicle(std::shared_ptr<Vehicle> vehicle)
{
    m_vehicle = vehicle;
}
std::shared_ptr<Vehicle> Delivery::getVehicle() const 
{
    return m_vehicle;
}
std::shared_ptr<Store> Delivery::getStore() const
{
    return m_store;
}
