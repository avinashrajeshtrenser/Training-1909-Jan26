#pragma once
#include <iostream>

class User
{
private:
	std::string m_userName;
	std::string m_password;
	int m_userId;
	bool m_isActive;
public:
	User() : m_userId{ 0 }, m_userName{ "" }, m_password{ "" },  m_isActive{true} {}
	User(int userId, std::string userName, std::string password ) : m_userId{ userId }, m_userName{ userName }, m_password{ password },  m_isActive{ true }{}
	std::string getUserName();
	std::string getPassword();
	int getUserId() const;
	bool isActive();
	void setIsActive(bool);
	std::string serialize();
	virtual std::string getRole() const = 0;
	static std::shared_ptr<User> deserialize(const std::string& line);
};
