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

string Product::getStatus() const
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

string Product::serialize() const
{
    return to_string(m_productId) + "|" +
        m_productName + "|" +
        to_string(m_stockQuantity) + "|" +
        to_string(m_qualityScore) + "|" +
        m_status;
}

Product Product::deserialize(const string& line)
{
    stringstream ss(line);
    string token;
    int id, stock, quality;
    string name, status;

    getline(ss, token, '|'); id = stoi(token);
    getline(ss, name, '|');
    getline(ss, token, '|'); stock = stoi(token);
    getline(ss, token, '|'); quality = stoi(token);
    getline(ss, status, '|');

    Product p(id, name, stock, quality);
    p.updateStatus(status);
    return p;
}