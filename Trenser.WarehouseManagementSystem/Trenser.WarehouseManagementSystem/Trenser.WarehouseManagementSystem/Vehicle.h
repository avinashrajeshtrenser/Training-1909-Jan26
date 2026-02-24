#pragma once
#include <iostream>
class Vehicle
{
private:
	int m_vehicleId;
	std::string m_driverName;
	int m_capacity;
	bool m_isAvailable;
	bool m_isActive;
public:
	Vehicle() : m_vehicleId(0), m_driverName(""), m_capacity(0), m_isAvailable(false), m_isActive("Active") {}
	Vehicle(int vehicleId, std::string driverName, int capacity, bool isAvailable) : m_vehicleId(vehicleId), m_driverName(driverName), m_capacity(capacity), m_isAvailable(isAvailable), m_isActive("Active") {}
	int getVehicleId() const;
	int getcapacity() const;
	std::string getdriverName() const;
	bool isActive() const;
	void setIsActive(bool);
	bool getIsAvailable() const;
	void setIsAvailable(bool available);
	std::string serialize() const;
	static Vehicle deserialize(const std::string& line);
};

