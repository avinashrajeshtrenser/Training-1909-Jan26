#include <string>
#include <sstream>
#include "Store.h"
using namespace std;
int Store::getStoreId() const
{
    return m_storeId;
}

string Store::getStoreName() const
{
    return m_storeName;
}

string Store::getStoreLocation() const
{
    return m_location;
}

bool Store::isActive() const
{
    return m_isActive;
}

void Store::setIsActive(bool status)
{
    m_isActive = status;
}

string Store::serialize() const
{
    return to_string(m_storeId) + "|" +
        m_storeName + "|" +
        m_location + "|" +
        to_string(m_isActive);
}

Store Store::deserialize(const string& line)
{
    try
    {
        stringstream ss(line);
        string token;
        int id;
        string name, location;
        getline(ss, token, '|'); id = stoi(token);
        getline(ss, name, '|');
        getline(ss, location, '|');
        getline(ss, token, '|');
        Store store(id, name, location);
        store.setIsActive(stoi(token));
        return store;
    }
    catch (...)
    {
        throw runtime_error("Error parsing file");
    }
}