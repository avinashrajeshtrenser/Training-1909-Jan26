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
	Product() : m_productId(0), m_productName(""), m_stockQuantity(0), m_qualityScore(0), m_status("Unchecked") {}
	Product(int productId, std::string productName, int stockQuantity, int qualityScore) : m_productId(productId), m_productName(productName), m_stockQuantity(stockQuantity), m_qualityScore(qualityScore), m_status("Unchecked") {}
	int getProductId();
	int getStockQuantity();
	int getQualityScore();
	std::string getproductName();
	std::string getStatus();
	void updateStock(int quantity);
	void updateStatus(std::string status);
};

