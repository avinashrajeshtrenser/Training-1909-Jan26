using namespace std;
#include "DeliveryItem.h"

DeliveryItem::DeliveryItem(int quantity, std::shared_ptr<Product> product, std::shared_ptr<Store> store)
{
    m_quantity = quantity;
    m_store = store;
    if (product)
    {
        m_product = make_shared<Product>(*product);
    }
}

shared_ptr<Product> DeliveryItem::getProduct() const {
    return m_product;
}
shared_ptr<Store> DeliveryItem::getStore() const {
    return m_store;
}
int DeliveryItem::getQuantity() const {
    return m_quantity;
}
