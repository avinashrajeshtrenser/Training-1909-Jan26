#pragma once
#include <iostream>
class Store
{
private:
	int m_storeId;
	std::string m_storeName;
	std::string m_location;
public:
	Store() :m_storeId(0), m_storeName(""), m_location("") {}
	Store(int storeId, std::string storeName, std::string location) : m_storeId(storeId), m_storeName(storeName), m_location(location) {}
	int getStoreId() const;
	std::string getStoreName() const;
	std::string getStoreLocation() const;
};