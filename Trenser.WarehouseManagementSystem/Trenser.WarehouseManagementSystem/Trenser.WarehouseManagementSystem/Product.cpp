using namespace std;
#include "Product.h"

int Product::getProductId()
{
    return m_productId;
}
int Product::getStockQuantity()
{
    return m_stockQuantity;
}
int Product::getQualityScore()
{
    return m_qualityScore;
}

string Product::getproductName()
{
    return m_productName;
}

std::string Product::getStatus()
{
    return m_status;
}

void Product::updateStockIncrease(int quantity)
{
    m_stockQuantity += quantity;
}

void Product::updateStatus(string status)
{
    m_status = status;
}

