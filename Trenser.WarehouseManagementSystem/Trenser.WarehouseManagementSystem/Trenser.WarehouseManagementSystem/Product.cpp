#include <sstream>
#include <string>
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

ProductStatus Product::getStatus() const
{
    return m_status;
}

void Product::updateStock(int quantity)
{
    m_stockQuantity += quantity;
}

void Product::updateStatus(ProductStatus status)
{
    m_status = status;
}

string Product::serialize() const
{
    return to_string(m_productId) + "|" +
        m_productName + "|" +
        to_string(m_stockQuantity) + "|" +
        to_string(m_qualityScore) + "|" +
        to_string(static_cast<int>(m_status));
}

Product Product::deserialize(const string& line)
{
    try
    {
        stringstream ss(line);
        string token;
        int id, stock, quality, statusInt;
        string name;
        getline(ss, token, '|'); 
        id = stoi(token);
        getline(ss, name, '|');
        getline(ss, token, '|'); 
        stock = stoi(token);
        getline(ss, token, '|'); 
        quality = stoi(token);
        getline(ss, token, '|');
        statusInt = stoi(token);
        if (statusInt < static_cast<int>(ProductStatus::ACTIVE) && statusInt > static_cast<int>(ProductStatus::REMOVED))
        {
            throw runtime_error("Invalid Product Status");
        }
        Product product(id, name, stock, quality);
        product.updateStatus(static_cast<ProductStatus>(statusInt));
        return product;
    }
    catch (...)
    {
        throw runtime_error("Error parsing file");
    }
}