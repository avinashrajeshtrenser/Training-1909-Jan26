#pragma once
#include <iostream>
class Product
{
private:
	int m_productId;
	std::string m_productName;
	int m_stockQuantity;
	int m_qualityScore;
	std::string m_status;
public:
	Product getProductDetails();
	void updateStatus();
};

