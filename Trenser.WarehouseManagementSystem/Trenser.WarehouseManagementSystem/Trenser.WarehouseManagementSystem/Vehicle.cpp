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

