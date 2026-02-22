#include "User.h"

int User::getUserId()
{
    return m_userId;
}
std::string User::getUserStatus()
{
    return m_userStatus;
}
void User::updateUserStatus(std::string status)
{
    m_userStatus = status;
}
std::string User::getUserName()
{
    return m_userName;
}
std::string User::getPassword()
{
    return m_password;
}
std::string User::getRole()
{
    return m_role;
}
