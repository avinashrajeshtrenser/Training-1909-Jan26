#pragma once
#include <iostream>
#include <vector>
#include "User.h"
#include "Delivery.h"
#include "Vehicle.h"
#include "Store.h"
class Manager : public User
{
private:
	std::vector<Delivery> m_deliveries;
	std::vector<Vehicle> m_vehicle;
	std::vector<Store> m_store;
public:
	Manager() : m_deliveries(), m_vehicle(), m_store() {}
	Manager(int userId, std::string userName, std::string password, std::string role) : User(userId, userName, password, role), m_deliveries(), m_vehicle(), m_store() {}
	std::vector<Vehicle> getAllManagedVehicles();
	std::vector<Store> getAllManagedStore();
	std::vector<Delivery> getAllDelivery();
	void dispatchProduct();
	void addstore(Store& store);
	void addVehicle(Vehicle& vehicle);
};

