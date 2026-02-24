#include <string>
#include <sstream>
using namespace std;
#include "User.h"
#include "Manager.h"
#include "Staff.h"
#include "Admin.h"

int User::getUserId() const
{
    return m_userId;
}

string User::getUserStatus()
{
    return m_userStatus;
}

void User::updateUserStatus(string status)
{
    m_userStatus = status;
}

string User::getUserName()
{
    return m_userName;
}

string User::getPassword()
{
    return m_password;
}

string User::serialize()
{
    User* user;
    std::string role;
    if (user = dynamic_cast<Manager*>(this))
    {
        role = user->getRole();
    }
    else if (user = dynamic_cast<Staff*>(this))
    {
        role = user->getRole();
    }
    else if (user = dynamic_cast<Admin*>(this))
    {
        role = user->getRole();
    }
    return to_string(m_userId) + "|" +
        m_userName + "|" +
        m_password + "|" +
        role + "|" +
        m_userStatus;
}

std::shared_ptr<User> User::deserialize(const string& line)
{
    stringstream ss(line);
    string token;
    int id;
    string name, password, role, status;
    getline(ss, token, '|'); id = stoi(token);
    getline(ss, name, '|');
    getline(ss, password, '|');
    getline(ss, role, '|');
    getline(ss, status, '|');
    std::shared_ptr<User> user;
    if (role == "Manager")
    {
        user = std::make_shared<Manager>(id, name, password);
        user->updateUserStatus(status);
    }
    else if (role == "Staff")
    {
        user = std::make_shared<Staff>(id, name, password);
        user->updateUserStatus(status);
    }
    else if (role == "Admin")
    {
        user = std::make_shared<Admin>(id, name, password);
        user->updateUserStatus(status);
    }
    return user;
}
