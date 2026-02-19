    #pragma once
    #include <iostream>
    #include <vector>
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
        std::vector<Product> m_products;
        std::vector<Delivery> m_deliveries;
        std::vector<Vehicle> m_vehicles;
        std::vector<Store> m_stores;
        QualityCheck m_qualityCheck;
        std::vector<User> m_users;
        User m_autherizedUser;
        Menu* m_menu; 
        FileManager fileManager;

    public:
        WarehouseController() : m_menu(nullptr) {};
        void controllerMenu();
        bool authorizeUser(const std::string& username, const std::string& password);
        void loginUser();
        void addUser();
        void addVehicle();
        void addStore();
        void addProduct();
        void removeProduct(int productId);
        void dispatchProduct(int productId, int storeId);
        void listProducts() const;
        void acceptDelivery(const Delivery& delivery);
        void listDeliveries() const;
        void loadSystem();
        void saveSystem();
    };
