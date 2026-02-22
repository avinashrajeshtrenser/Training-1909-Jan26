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

string Store::getStoreStatus() const
{
    return m_storeStatus;
}

void Store::setStoreStatus(string status)
{
    m_storeStatus = status;
}

string Store::serialize() const
{
    return to_string(m_storeId) + "|" +
        m_storeName + "|" +
        m_location + "|" +
        m_storeStatus;
}

Store Store::deserialize(const string& line)
{
    stringstream ss(line);
    string token;
    int id;
    string name, location, status;
    getline(ss, token, '|'); id = stoi(token);
    getline(ss, name, '|');
    getline(ss, location, '|');
    getline(ss, status, '|');
    Store store(id, name, location);
    store.setStoreStatus(status);
    return store;
}