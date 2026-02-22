#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "Product.h"
#include "Delivery.h"
#include "Vehicle.h"
#include "Store.h"
#include "QualityCheck.h"
#include "User.h"
#include "Menu.h"
#include "AdminMenu.h"
#include "ManagerMenu.h"
#include "StaffMenu.h"
#include "FileManager.h"

class WarehouseController
{
private:
    std::shared_ptr<std::vector<Product>> m_products;
    std::shared_ptr<std::vector<Delivery>> m_deliveries;
    std::shared_ptr<std::vector<Vehicle>> m_vehicles;
    std::shared_ptr<std::vector<Store>> m_stores;
    std::shared_ptr<std::vector<DeliveryItem>> m_dispatchPendingProduct;
    std::shared_ptr<std::vector<DeliveryItem>> m_damagedProducts;
    QualityCheck m_qualityCheck;
    std::shared_ptr<std::vector<User>> m_users;
    User m_autherizedUser;
    Menu* m_menu;
    FileManager fileManager;
public:
    WarehouseController()
        : m_products(std::make_shared<std::vector<Product>>()),
        m_deliveries(std::make_shared<std::vector<Delivery>>()),
        m_vehicles(std::make_shared<std::vector<Vehicle>>()),
        m_stores(std::make_shared<std::vector<Store>>()),
        m_dispatchPendingProduct(std::make_shared<std::vector<DeliveryItem>>()),
        m_damagedProducts(std::make_shared<std::vector<DeliveryItem>>()),
        m_users(std::make_shared<std::vector<User>>()),
        m_menu(nullptr) {
    }
    void controllerMenu();
    bool authorizeUser(const std::string& username, const std::string& password);
    void loginUser();
    void addUser();
    void addVehicle();
    void addStore();
    void addProduct();
    void performQualityCheck();
    void removeUser();
    void removeProduct();
    void removeVehicle();
    void removeStore();
    void dispatchProduct();
    void listProducts() const;
    void listVehicles() const;
    void listDeliveries() const;
    void listDispatchPendingItems();
    void listStores() const;
    void acceptDelivery();
    void updateDeliveryStatus();
    void loadSystem();
    void saveSystem();
    std::shared_ptr<std::vector<Product>> getProducts();
    std::shared_ptr<std::vector<User>> getUsers();
    std::shared_ptr<std::vector<Vehicle>> getVehicles();
    std::shared_ptr<std::vector<Store>> getStores();
};
