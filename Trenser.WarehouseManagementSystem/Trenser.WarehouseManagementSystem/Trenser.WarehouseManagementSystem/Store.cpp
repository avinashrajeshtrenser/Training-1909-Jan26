#include "Store.h"

int Store::getStoreId() const
{
    return m_storeId;
}
std::string Store::getStoreName() const
{
    return m_storeName;
}
std::string Store::getStoreLocation() const
{
    return m_location;
}
std::string Store::getStoreStatus() const
{
    return m_storeStatus;
}

void Store::setStoreStatus(std::string status)
{
    m_storeStatus = status;
}
