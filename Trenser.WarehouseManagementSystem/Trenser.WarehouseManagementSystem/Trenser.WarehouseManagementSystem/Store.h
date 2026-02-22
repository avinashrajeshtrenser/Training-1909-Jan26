#pragma once
#include <iostream>
class Store
{
private:
	int m_storeId;
	std::string m_storeName;
	std::string m_location;
	std::string m_storeStatus;
public:
	Store() :m_storeId(0), m_storeName(""), m_location(""), m_storeStatus("Active") {}
	Store(int storeId, std::string storeName, std::string location) : m_storeId(storeId), m_storeName(storeName), m_location(location), m_storeStatus("Active") {}
	int getStoreId() const;
	std::string getStoreName() const;
	std::string getStoreLocation() const;
	std::string getStoreStatus() const;
	void setStoreStatus(std::string& status);
};