using namespace std;
#include "Product.h"

int Product::getProductId() const
{
    return m_productId;
}
int Product::getStockQuantity() const
{
    return m_stockQuantity;
}
int Product::getQualityScore() const
{
    return m_qualityScore;
}

string Product::getProductName() const
{
    return m_productName;
}

std::string Product::getStatus() const
{
    return m_status;
}

void Product::updateStock(int quantity)
{
    m_stockQuantity += quantity;
}

void Product::updateStatus(string status)
{
    m_status = status;
}

