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
	Staff(int userId, std::string userName, std::string password) : User(userId, userName, password), m_delivery() {}
	void performQualityCheck();
	void acceptDelivery();
    std::string getRole() const override;
};

