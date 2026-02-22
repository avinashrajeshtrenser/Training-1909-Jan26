#include <string>
#include <sstream>
using namespace std;
#include "User.h"

int User::getUserId()
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

string User::getRole()
{
    return m_role;
}

string User::serialize() const
{
    return to_string(m_userId) + "|" +
        m_userName + "|" +
        m_password + "|" +
        m_role + "|" +
        m_userStatus;
}

User User::deserialize(const string& line)
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

    User user(id, name, password, role);
    user.updateUserStatus(status);
    return user;
}