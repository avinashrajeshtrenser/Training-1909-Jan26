using namespace std;
#include "DeliveryItem.h"

shared_ptr<Product> DeliveryItem::getProduct() const {
    return m_product;
}
shared_ptr<Store> DeliveryItem::getStore() const {
    return m_store;
}
int DeliveryItem::getQuantity() const {
    return m_quantity;
}
