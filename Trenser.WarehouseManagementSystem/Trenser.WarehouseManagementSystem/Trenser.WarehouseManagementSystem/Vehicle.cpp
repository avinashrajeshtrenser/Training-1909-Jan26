#include "Vehicle.h"

int Vehicle::getVehicleId() const
{
    return m_vehicleId;
}
int Vehicle::getcapacity() const
{
    return m_capacity;
}
std::string Vehicle::getdriverName() const
{
    return m_driverName;
}
bool Vehicle::getIsAvailable() const
{
    return m_isAvailable;
}
void Vehicle::setIsAvailable(bool available)
{
     m_isAvailable = available;
}
std::string Vehicle::getStatus() const
{
    return m_status;
}
void Vehicle::setStatus(const std::string& status)
{
    m_status = status;
}
