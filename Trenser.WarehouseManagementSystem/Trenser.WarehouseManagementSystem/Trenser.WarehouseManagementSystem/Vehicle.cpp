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

string Vehicle::getStatus() const
{
    return m_status;
}

void Vehicle::setStatus(const string& status)
{
    m_status = status;
}

string Vehicle::serialize() const
{
    return to_string(m_vehicleId) + "|" +
        m_driverName + "|" +
        to_string(m_capacity) + "|" +
        to_string(m_isAvailable) + "|" +
        m_status;
}

Vehicle Vehicle::deserialize(const string& line)
{
    stringstream ss(line);
    string token;
    int id, capacity;
    bool available;
    string driver, status;
    getline(ss, token, '|'); id = stoi(token);
    getline(ss, driver, '|');
    getline(ss, token, '|'); capacity = stoi(token);
    getline(ss, token, '|'); available = stoi(token);
    getline(ss, status, '|');
    Vehicle vehicle(id, driver, capacity, available);
    vehicle.setStatus(status);
    return vehicle;
}