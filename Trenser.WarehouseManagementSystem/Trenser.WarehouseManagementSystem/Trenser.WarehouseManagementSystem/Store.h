#pragma once
#include <iostream>

class Store
{
private:
	int m_storeId;
	std::string m_storeName;
	std::string m_location;
	bool m_isActive;
public:
	Store() :m_storeId(0), m_storeName(""), m_location(""), m_isActive(true) {}
	Store(int storeId, std::string storeName, std::string location) : m_storeId(storeId), m_storeName(storeName), m_location(location), m_isActive(true) {}
	int getStoreId() const;
	std::string getStoreName() const;
	std::string getStoreLocation() const;
	bool isActive() const;
	void setIsActive(bool);
	std::string serialize() const;
	static Store deserialize(const std::string& line);
};