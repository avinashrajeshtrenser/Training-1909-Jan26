#pragma once
#include <iostream>
class Vehicle
{
private:
	int m_vehicleId;
	std::string m_driverName;
	int m_capacity;
	bool m_isAvailable;
	std::string m_status;
public:
	Vehicle() : m_vehicleId(0), m_driverName(""), m_capacity(0), m_isAvailable(false), m_status("Active") {}
	Vehicle(int vehicleId, std::string driverName, int capacity, bool isAvailable) : m_vehicleId(vehicleId), m_driverName(driverName), m_capacity(capacity), m_isAvailable(isAvailable), m_status("Active") {}
	int getVehicleId() const;
	int getcapacity() const;
	std::string getdriverName() const;
	std::string getStatus() const;
	bool getIsAvailable() const;
	void setIsAvailable(bool available);
	void setStatus(const std::string& status);
	
};

