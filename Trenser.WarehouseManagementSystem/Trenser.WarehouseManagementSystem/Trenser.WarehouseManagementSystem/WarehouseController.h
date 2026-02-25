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
#include "ReadUtility.h"

class WarehouseController {
private:
    std::vector<std::shared_ptr<Product>> m_products;
    std::vector<std::shared_ptr<Vehicle>> m_vehicles;
    std::vector<std::shared_ptr<Store>> m_stores;
    std::vector<std::shared_ptr<User>> m_users;
    std::vector<DeliveryItem> m_dispatchPendingProduct;
    std::vector<DeliveryItem> m_damagedProducts;
    std::vector<Delivery> m_deliveries;
    QualityCheck m_qualityCheck;
    std::shared_ptr<User> m_autherizedUser;
    std::unique_ptr<Menu> m_menu;
    FileManager fileManager;
    static const std::string PRODUCT_FILE;
    static const std::string VEHICLE_FILE;
    static const std::string STORE_FILE;
    static const std::string USER_FILE; 
    static const std::string DELIVERY_FILE;
    static const std::string DISPATCH_FILE; 
    static const std::string DAMAGED_FILE;
public:
    WarehouseController() {}
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
    void addToDispatchQueue();
    void dispatchDelivery();
    void updateDeliveryStatus();
    void listUsers() const;
    void listProducts() const;
    void listVehicles() const;
    void listStores() const;
    void listDeliveries() const;
    void listDispatchPendingItems() const;
    void loadSystem();
    void saveSystem();
    std::shared_ptr<Product> selectProduct(int productId);
    std::shared_ptr<Store> selectStore(int storeId);
    bool validateStock(std::shared_ptr<Product> product, int quantity);
    void queueDispatch(std::shared_ptr<Product> product, std::shared_ptr<Store> store, int quantity);
    bool hasPendingItem() const;
    std::map<std::shared_ptr<Store>, std::vector<DeliveryItem>> groupItemsByStore() const;
    Delivery createDeliveryForStore(const std::shared_ptr<Store>& store, const std::vector<DeliveryItem>& items);
    std::shared_ptr<Vehicle> selectVehicleForStore(const std::shared_ptr<Store>& store);
    void confirmAndSaveDelivery(Delivery& delivery, const std::shared_ptr<Vehicle>& vehicle);
    void removeApprovedItemsFromQueue();
    std::vector<std::shared_ptr<Product>>& getProducts();
    std::vector<std::shared_ptr<User>>& getUsers();
    std::vector<std::shared_ptr<Vehicle>>& getVehicles();
    std::vector<std::shared_ptr<Store>>& getStores();
};
