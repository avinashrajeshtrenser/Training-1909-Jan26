#pragma once
#include <iostream>
#include <vector>
#include "User.h"
#include "Delivery.h"
class Staff : public User
{
private:
	std::vector<Delivery> m_delivery;
public:
	Staff() : m_delivery() {}
	Staff(int userId, std::string userName, std::string password, std::string role) : User(userId, userName, password, role), m_delivery() {}
	void performQualityCheck();
	void UpdateDelivery();
	void acceptDelivery();
};

