#pragma once
#include <iostream>
class User
{
private:
	std::string m_userName;
	std::string m_password;
	int m_userId;
	std::string m_role;
	std::string m_userStatus;
public:
	User() : m_userId{ 0 }, m_userName{ "" }, m_password{ "" }, m_role{ "" }, m_userStatus{"Signed Out"} {}
	User(int userId, std::string userName, std::string password, std::string role) : m_userId{ userId }, m_userName{ userName }, m_password{ password }, m_role{ role } {}
	std::string getRole();
	std::string getUserName();
	std::string getPassword();
	int getUserId();
	void updateUserStatus(std::string status);
};

