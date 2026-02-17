#pragma once
#include <iostream>
class User
{
private:
	std::string m_userName;
	std::string m_password;
	int m_userId;
	std::string m_role;
public:
	User() : m_userId{ 0 }, m_userName{ "" }, m_password{ "" }, m_role{ "" } {}
	User(int userId, std::string userName, std::string password, std::string role) : m_userId{ userId }, m_userName{ userName }, m_password{ password }, m_role{ role } {}
	std::string getRole();
};

