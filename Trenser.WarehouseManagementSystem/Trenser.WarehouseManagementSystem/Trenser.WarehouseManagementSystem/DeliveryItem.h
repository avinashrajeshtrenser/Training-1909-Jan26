#pragma once
#include <iostream>
#include "Product.h"
class DeliveryItem
{
private:
	int m_quantity;
	Product m_product;
public:
	DeliveryItem() : m_quantity(0), m_product() {}
	DeliveryItem(int quantity, Product product) : m_quantity(quantity), m_product(product);
	Product getProduct();
};

