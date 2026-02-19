#pragma once
#include <iostream>
class Vehicle
{
private:
	int m_vehicleId;
	std::string m_driverName;
	int m_capacity;
	bool m_isAvailable;
public:
	Vehicle() : m_vehicleId(0), m_driverName(""), m_capacity(0), m_isAvailable(false) {}
	Vehicle(int vehicleId, std::string driverName, int capacity, bool isAvailable) : m_vehicleId(vehicleId), m_driverName(driverName), m_capacity(capacity), m_isAvailable(isAvailable) {}
	int getVehicleId();
	int getcapacity();
	std::string getdriverName();
	bool getIsAvailable();
};

