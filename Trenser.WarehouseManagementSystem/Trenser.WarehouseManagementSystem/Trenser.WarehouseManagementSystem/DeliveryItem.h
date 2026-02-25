#pragma once
#include <memory>
#include "Product.h"
#include "Store.h"

class DeliveryItem {
private:
    int m_quantity;
    std::shared_ptr<Product> m_product;
    std::shared_ptr<Store> m_store;
public:
    DeliveryItem() : m_quantity(0), m_product(nullptr), m_store(nullptr) {}
    DeliveryItem(int quantity, std::shared_ptr<Product> product, std::shared_ptr<Store> store);
    std::shared_ptr<Product> getProduct() const;
    std::shared_ptr<Store> getStore() const;
    int getQuantity() const;
};
