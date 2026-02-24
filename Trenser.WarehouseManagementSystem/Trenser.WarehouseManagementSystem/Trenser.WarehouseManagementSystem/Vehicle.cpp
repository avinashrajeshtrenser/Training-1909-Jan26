#include <string>
#include <sstream>
using namespace std;
#include "Vehicle.h"

int Vehicle::getVehicleId() const
{
    return m_vehicleId;
}

int Vehicle::getcapacity() const
{
    return m_capacity;
}

string Vehicle::getdriverName() const
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

bool Vehicle::isActive() const
{
    return m_isActive;
}

void Vehicle::setIsActive(bool isActive)
{
    m_isActive = isActive;
}

string Vehicle::serialize() const
{
    return to_string(m_vehicleId) + "|" +
        m_driverName + "|" +
        to_string(m_capacity) + "|" +
        to_string(m_isAvailable) + "|" +
        to_string(m_isActive);
}

Vehicle Vehicle::deserialize(const string& line)
{
    try
    {
        stringstream ss(line);
        string token;
        int id, capacity;
        bool isAvailable, isActive;
        string driver;
        getline(ss, token, '|');
        id = stoi(token);
        getline(ss, driver, '|');
        getline(ss, token, '|');
        capacity = stoi(token);
        getline(ss, token, '|');
        isAvailable = stoi(token);
        getline(ss, token, '|');
        isActive = stoi(token);
        Vehicle vehicle(id, driver, capacity, isAvailable);
        vehicle.setIsActive(isActive);
        return vehicle;
    }
    catch (...)
    {
        throw std::runtime_error("Error parsing file");
    }
}