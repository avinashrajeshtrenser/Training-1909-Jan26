#pragma once
#include <iostream>
#include <vector>
#include "DeliveryItem.h"
class Delivery
{
private:
	int m_deliveryId;
	std::string m_deliveryStatus;
	std::string m_deliveryAddress;
	std::vector<DeliveryItem> m_item;
public:
	void updateDeliveryStatus();
	std::vector<DeliveryItem> getItems();
};

