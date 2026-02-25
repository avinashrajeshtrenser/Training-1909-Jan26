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

bool User::isActive()
{
    return m_isActive;
}

void User::setIsActive(bool status)
{
    m_isActive = status;
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
        to_string(m_isActive);
}

std::shared_ptr<User> User::deserialize(const string& line)
{
    stringstream userStream(line);
    string token;
    int id;
    string name, password, role, status;
    getline(userStream, token, '|');
    id = stoi(token);
    getline(userStream, name, '|');
    getline(userStream, password, '|');
    getline(userStream, role, '|');
    getline(userStream, status, '|');
    std::shared_ptr<User> user;
    if (role == "Manager")
    {
        user = std::make_shared<Manager>(id, name, password);
    }
    else if (role == "Staff")
    {
        user = std::make_shared<Staff>(id, name, password);
    }
    else if (role == "Admin")
    {
        user = std::make_shared<Admin>(id, name, password);
    }
    user->setIsActive(stoi(token));
    return user;
}

