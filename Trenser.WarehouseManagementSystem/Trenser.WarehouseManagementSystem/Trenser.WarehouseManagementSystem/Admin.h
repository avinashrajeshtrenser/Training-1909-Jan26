#pragma once
#include <iostream>
#include "User.h"
class Admin : public User
{
public:
	Admin() {}
	Admin(int userId, std::string userName, std::string password, std::string role) : User(userId, userName, password, role) {}
};

