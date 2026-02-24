#pragma once
#include <iostream>
#include "User.h"
class Admin : public User
{
public:
	Admin() {}
	Admin(int userId, std::string userName, std::string password) : User(userId, userName, password) {}
    std::string getRole() const override;
};

