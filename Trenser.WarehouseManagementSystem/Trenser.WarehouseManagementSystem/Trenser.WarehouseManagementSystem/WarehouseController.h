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

class WarehouseController {
private:
    std::vector<std::shared_ptr> m_products;
    std::vector<std::shared_ptr> m_vehicles;
    std::vector<std::shared_ptr> m_stores;
    std::vector<std::shared_ptr> m_users;
    std::vector m_dispatchPendingProduct;
    std::vector m_damagedProducts;
    std::vector m_deliveries;
    QualityCheck m_qualityCheck;
    User m_autherizedUser;
    std::unique_ptr<Menu> m_menu;
    FileManager fileManager;
public:
    WarehouseController();
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
    void acceptDelivery();
    void updateDeliveryStatus();
    void listUsers() const;
    void listProducts() const;
    void listVehicles() const;
    void listStores() const;
    void listDeliveries() const;
    void listDispatchPendingItems() const;
    void loadSystem();
    void saveSystem();
    std::vector<std::shared_ptr<Product>>& getProducts();
    std::vector<std::shared_ptr<User>>& getUsers();
    std::vector<std::shared_ptr<Vehicle>>& getVehicles();
    std::vector<std::shared_ptr<Store>>& getStores();
};
