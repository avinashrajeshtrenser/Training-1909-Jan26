using namespace std;
#include "WarehouseController.h"

WarehouseController::WarehouseController()
{
    loadSystem();
}

void WarehouseController::controllerMenu() {
    int choice;
    do 
    {
        cout << "\n=========WareHouse Management===========\n";
        cout << "1. Register\n2. Login\n3. Exit\n\nEnter the choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addUser();
            break;
        case 2:
            loginUser();
            break;
        case 3:
            saveSystem();
            cout << "Exiting.....";
            break;
        default:
            cout << "Invalid Input. Try again\n";
            break;
        }
    } while (choice != 3);
}

bool WarehouseController::authorizeUser(const string& username, const string& password)
{
    for (auto it = m_users.begin(); it != m_users.end(); ++it)
    {
        if ((*it)->getUserName() == username && (*it)->getPassword() == password)
        {
            m_autherizedUser = *(*it);
            return true;
        }
    }
    return false;
}

void WarehouseController::loginUser() {
    string username, password;
    cout << "Username : ";
    cin >> username;
    cout << "Password : ";
    cin >> password;
    if (authorizeUser(username, password))
    {
        cout << "Login Successfull ! Welcome " << m_autherizedUser.getUserName() << endl;
        if (m_autherizedUser.getRole() == "Admin")
        {
            m_menu = make_unique<AdminMenu>();
        }
        else if (m_autherizedUser.getRole() == "Manager")
        {
            m_menu = make_unique<ManagerMenu>();
        }
        else if (m_autherizedUser.getRole() == "Staff")
        {
            m_menu = make_unique<StaffMenu>();
        }
        if (m_menu != nullptr)
        {
            m_menu->handleOperation(*this);
            saveSystem();
        }
        else
        {
            cout << "\nError: No menu available for role '" << m_autherizedUser.getRole() << "'\n";
        }
    }
    else
    {
        cout << "Invalid Credentials.Try Again\n";
    }
}

void WarehouseController::addUser() {
    string username, password, role;
    int roleChoice;
    cout << "Enter the Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;
    cout << "Select Role:\n1. Manager\n2. Staff\n3. Admin\nEnter choice: ";
    cin >> roleChoice;
    if (roleChoice == 1)
    {
        role = "Manager";
    }
    else if (roleChoice == 2)
    {
        role = "Staff";
    }
    else if (roleChoice == 3)
    {
        role = "Admin";
    }
    else
    {
        cout << "Invalid role selection.\n";
        return;
    }
    for (auto it = m_users.begin(); it != m_users.end(); ++it)
    {
        if ((*it)->getUserName() == username)
        {
            std::cout << "Error: Username '" << username << "' already exists.\n";
            return;
        }
    }
    int userId = static_cast<int>(m_users.size()) + 101;
    shared_ptr<User> newUser = make_shared<User>(userId, username, password, role);
    m_users.push_back(newUser);
    cout << "User '" << username << "' registered successfully as " << role << ".\n";
    saveSystem();
}

void WarehouseController::addVehicle()
{
    try
    {
        int capacity, availabilityInput;
        std::string driverName;
        bool isAvailable;
        std::cout << "Enter the Capacity: ";
        std::cin >> capacity;
        std::cout << "Enter the Driver Name: ";
        std::cin >> driverName;
        std::cout << "Is the Car Available for Delivery: \n1. Available\n2. Not Available\nEnter Your choice : ";
        std::cin >> availabilityInput;
        switch (availabilityInput)
        {
        case 1:
            isAvailable = true;
            break;
        case 2:
            isAvailable = false;
            break;
        default:
            cout << "Invalid Input...\n";
            break;
        }
        int vehicleId = static_cast<int>(m_vehicles.size()) + 101;
        for (auto it = m_vehicles.begin(); it != m_vehicles.end(); ++it)
        {
            if ((*it)->getVehicleId() == vehicleId)
            {
                throw std::runtime_error("Vehicle ID already exists.");
            }
        }
        std::shared_ptr<Vehicle> newVehicle = std::make_shared<Vehicle>(vehicleId, driverName, capacity, isAvailable);
        m_vehicles.push_back(newVehicle);
        std::cout << "Vehicle '" << vehicleId << "' added successfully.\n";
        saveSystem();
    }
    catch (const std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << "\n";
    }
}

void WarehouseController::addProduct()
{
    try
    {
        int productId, qualityScore, stockQuantity;
        std::string productName;
        std::cout << "Enter the Product Name : ";
        std::cin >> productName;
        std::cout << "Enter the Stock quantity : ";
        std::cin >> stockQuantity;
        std::cout << "Enter the Quality score : ";
        std::cin >> qualityScore;
        productId = static_cast<int>(m_products.size()) + 101;
        for (auto it = m_products.begin(); it != m_products.end(); ++it)
        {
            if ((*it)->getProductId() == productId)
            {
                throw std::runtime_error("Product ID already exists.");
            }
        }
        std::shared_ptr<Product> newProduct = std::make_shared<Product>(productId, productName, stockQuantity, qualityScore);
        m_products.push_back(newProduct);
        std::cout << "Product '" << productName << "' added successfully.\n";
        saveSystem();
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void WarehouseController::addStore()
{
    try
    {
        int storeId;
        std::string storeName, location;
        std::cout << "Enter the Store Name : ";
        std::cin >> storeName;
        std::cout << "Enter the Store Location : ";
        std::cin >> location;
        storeId = static_cast<int>(m_stores.size()) + 10;
        for (auto it = m_stores.begin(); it != m_stores.end(); ++it)
        {
            if ((*it)->getStoreId() == storeId)
            {
                throw std::runtime_error("Store ID already exists.");
            }
        }
        std::shared_ptr<Store> newStore = std::make_shared<Store>(storeId, storeName, location);
        m_stores.push_back(newStore);
        std::cout << "Store '" << storeName << "' added successfully.\n";
        saveSystem();
    }
    catch (const std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << "\n";
    }
}

void WarehouseController::dispatchProduct() {
    int productId, storeId, quantity;
    if (m_products.empty())
    {
        cout << "No product available to assign.\n";
        return;
    }
    listProducts();
    cout << "Enter the Product Id: ";
    cin >> productId;
    if (m_stores.empty())
    {
        cout << "No stores available to assign.\n";
        return;
    }
    listStores();
    cout << "Enter the Store Id: ";
    cin >> storeId;
    cout << "Enter the Quantity: ";
    cin >> quantity;
    shared_ptr<Product> selectedProduct = nullptr;
    shared_ptr<Store> selectedStore = nullptr;
    for (auto it = m_products.begin(); it != m_products.end(); ++it)
    {
        if ((*it)->getProductId() == productId && (*it)->getStatus() != "Removed")
        {
            if ((*it)->getStockQuantity() < quantity)
            {
                cout << "Error: Not enough stock for Product '" << productId << "'.\n";
                return;
            }
            (*it)->updateStock(-quantity);
            if ((*it)->getStockQuantity() == 0)
            {
                (*it)->updateStatus("Out of Stock");
            }
            selectedProduct = *it;
            break;
        }
    }
    if (!selectedProduct)
    {
        cout << "Error: Product '" << productId << "' not found.\n";
        return;
    }
    for (auto st = m_stores.begin(); st != m_stores.end(); ++st)
    {
        if ((*st)->getStoreId() == storeId && (*st)->getStoreStatus() != "Removed")
        {
            selectedStore = *st;
            break;
        }
    }
    if (!selectedStore)
    {
        cout << "Error: Store '" << storeId << "' not found.\n";
        return;
    }
    DeliveryItem item(quantity, selectedProduct, selectedStore);
    m_dispatchPendingProduct.push_back(item);
    cout << "Product '" << selectedProduct->getProductName() << "' queued for quality check before dispatch to Store '" << selectedStore->getStoreName() << "'.\n";
    saveSystem();
}

void WarehouseController::listUsers() const {
    if (m_users.empty())
    {
        cout << "No users registered.\n";
        return;
    }
    cout << "--- User List ---\n";
    for (auto it = m_users.begin(); it != m_users.end(); ++it)
    {
        if ((*it)->getUserStatus() == "Removed")
        {
            continue;
        }
        cout << "User ID: " << (*it)->getUserId()
            << " | Username: " << (*it)->getUserName()
            << " | Role: " << (*it)->getRole()
            << " | Status: " << (*it)->getUserStatus()
            << "\n";
    }
}

void WarehouseController::listVehicles() const {
    if (m_vehicles.empty())
    {
        cout << "No vehicles available.\n";
        return;
    }
    cout << "--- Vehicle List ---\n";
    for (auto it = m_vehicles.begin(); it != m_vehicles.end(); ++it)
    {
        if ((*it)->getStatus() != "Active")
        {
            continue;
        }
        cout << "Vehicle ID: " << (*it)->getVehicleId()
            << " | Driver: " << (*it)->getdriverName()
            << " | Capacity: " << (*it)->getcapacity()
            << " | Available: " << ((*it)->getIsAvailable() ? "Yes" : "No")
            << "\n";
    }
}

void WarehouseController::listProducts() const {
    if (m_products.empty())
    {
        cout << "No products available in the warehouse.\n";
        return;
    }
    cout << "\n--- Product List ---\n";
    for (auto it = m_products.begin(); it != m_products.end(); ++it)
    {
        if ((*it)->getStatus() == "Removed")
        {
            continue;
        }
        cout << "Product ID: " << (*it)->getProductId()
            << " | Name: " << (*it)->getProductName()
            << " | Stock: " << (*it)->getStockQuantity()
            << " | Quality Score: " << (*it)->getQualityScore()
            << " | Status: " << (*it)->getStatus()
            << "\n";
    }
}

void WarehouseController::listStores() const {
    if (m_stores.empty())
    {
        cout << "No stores registered.\n";
        return;
    }
    cout << "--- Store List ---\n";
    for (auto it = m_stores.begin(); it != m_stores.end(); ++it)
    {
        if ((*it)->getStoreStatus() == "Removed")
        {
            continue;
        }
        cout << "Store ID: " << (*it)->getStoreId()
            << " | Name: " << (*it)->getStoreName()
            << " | Location: " << (*it)->getStoreLocation()
            << "\n";
    }
}

void WarehouseController::listDispatchPendingItems() const {
    if (m_dispatchPendingProduct.empty())
    {
        cout << "No items pending to dispatch.\n";
        return;
    }
    cout << "--- Dispatch Pending Items ---\n";
    for (auto it = m_dispatchPendingProduct.begin(); it != m_dispatchPendingProduct.end(); ++it)
    {
        shared_ptr<Product> product = it->getProduct();
        if (product)
        {
            cout << "Product ID: " << product->getProductId()
                << " | Name: " << product->getProductName()
                << " | Quantity: " << it->getQuantity()
                << " | Status: " << product->getStatus()
                << "\n";
        }
    }
}

void WarehouseController::acceptDelivery()
{
    int deliveryId, vehicleId;
    std::shared_ptr<Vehicle> selectedVehicle = nullptr;
    if (m_dispatchPendingProduct.empty())
    {
        std::cout << "No items pending delivery.\n";
        return;
    }
    std::map<std::shared_ptr<Store>, std::vector<DeliveryItem>> storeGroups;
    for (auto it = m_dispatchPendingProduct.begin(); it != m_dispatchPendingProduct.end(); ++it)
    {
        storeGroups[it->getStore()].push_back(*it);
    }
    for (auto storeIt = storeGroups.begin(); storeIt != storeGroups.end(); ++storeIt)
    {
        std::shared_ptr<Store> store = storeIt->first;
        std::vector<DeliveryItem>& items = storeIt->second;
        deliveryId = static_cast<int>(m_deliveries.size()) + 1;
        std::shared_ptr<Vehicle> nullVehicle = nullptr;
        Delivery newDelivery(deliveryId, store->getStoreLocation(), store, nullVehicle);
        for (auto itemIt = items.begin(); itemIt != items.end(); ++itemIt)
        {
            newDelivery.getItems().push_back(*itemIt);
        }
        listVehicles();
        std::cout << "Enter Vehicle ID to assign for Store "<< store->getStoreLocation() << ": ";
        std::cin >> vehicleId;
        for (auto vehicleIt = m_vehicles.begin();vehicleIt != m_vehicles.end(); ++vehicleIt)
        {
            if ((*vehicleIt)->getVehicleId() == vehicleId && (*vehicleIt)->getIsAvailable() && (*vehicleIt)->getStatus() == "Active")
            {
                (*vehicleIt)->setIsAvailable(false);
                selectedVehicle = *vehicleIt;
                break;
            }
        }
        if (!selectedVehicle)
        {
            std::cout << "Vehicle not available. Skipping store.\n";
            continue;
        }
        newDelivery.assignVehicle(selectedVehicle);
        newDelivery.updateDeliveryStatus("In Transit");
        m_deliveries.push_back(newDelivery);
        std::cout << "Delivery " << deliveryId << " created for Store " << store->getStoreLocation() << "\n";
    }
    m_dispatchPendingProduct.clear();
    saveSystem();
}

void WarehouseController::updateDeliveryStatus()
{
    int deliveryId;
    listDeliveries();
    std::cout << "Enter Delivery ID to update: ";
    std::cin >> deliveryId;

    for (std::vector<Delivery>::iterator it = m_deliveries.begin(); it != m_deliveries.end(); ++it)
    {
        if (it->getDeliveryId() == deliveryId)
        {
            std::string currentStatus = it->getDeliveryStatus();
            std::cout << "Current status: " << currentStatus << "\n";
            int choice;
            std::cout << "Select new status:\n";
            std::cout << "1. Dispatched\n";
            std::cout << "2. In Transit\n";
            std::cout << "3. Delivered\nSelect your Choice : ";
            std::cin >> choice;
            if (currentStatus == "Delivered")
            {
                std::cout << "Error: Delivery is already completed and cannot be changed.\n";
                return;
            }
            if (currentStatus == "In Transit" && choice == 1)
            {
                std::cout << "Error: Cannot change status from In Transit back to Dispatched.\n";
                return;
            }
            switch (choice)
            {
            case 1:
                it->updateDeliveryStatus("Dispatched");
                break;
            case 2:
                it->updateDeliveryStatus("In Transit");
                break;
            case 3:
                it->updateDeliveryStatus("Delivered");
                if (it->getVehicle())
                {
                    it->getVehicle()->setIsAvailable(true);
                }
                break;
            default:
                std::cout << "Invalid status choice.\n";
                return;
            }
            std::cout << "Delivery " << deliveryId << " status updated successfully.\n";
            saveSystem();
            return;
        }
    }
    std::cout << "Error: Delivery with ID " << deliveryId << " not found.\n";
}

void WarehouseController::listDeliveries() const
{
    if (m_deliveries.empty())
    {
        cout << "No deliveries available.\n";
        return;
    }
    for (vector<Delivery>::const_iterator it = m_deliveries.begin(); it != m_deliveries.end(); ++it)
    {
        cout << "Delivery ID: " << it->getDeliveryId() << " | Status: " << it->getDeliveryStatus() << " | Address: " << it->getDeliveryAddress() << "\n";
        shared_ptr<Store> store = it->getStore();
        if (store)
        {
            cout << "  Store ID: " << store->getStoreId() << " | Location: " << store->getStoreLocation() << "\n";
        }
        shared_ptr<Vehicle> vehicle = it->getVehicle();
        if (vehicle)
        {
            cout << "  Vehicle ID: " << vehicle->getVehicleId() << " | Driver Name: " << vehicle->getdriverName() << " | Available: " << (vehicle->getIsAvailable() ? "Yes" : "No") << "\n";
        }
        cout << "  Items:\n";
        const vector<DeliveryItem>& items = it->getItems();
        for (vector<DeliveryItem>::const_iterator itemIt = items.begin(); itemIt != items.end(); ++itemIt)
        {
            shared_ptr<Product> product = itemIt->getProduct();
            if (product)
            {
                cout << "    Product ID: " << product->getProductId() << " | Name: " << product->getProductName() << " | Quantity: " << itemIt->getQuantity() << "\n";
            }
        }
        cout << "-----------------------------------\n";
    }
}

void WarehouseController::removeUser() {
    if (m_users.empty())
    {
        cout << "No user to Remove.\n";
        return;
    }
    listUsers();
    int userId;
    cout << "Enter User ID to remove: ";
    cin >> userId;
    for (auto it = m_users.begin(); it != m_users.end(); ++it)
    {
        if ((*it)->getUserId() == userId)
        {
            (*it)->updateUserStatus("Removed");
            cout << "User with ID " << (*it)->getUserName() << " removed successfully.\n";
            saveSystem();
            return;
        }
    }
    cout << "Error: User with ID " << userId << " not found.\n";
}

void WarehouseController::removeProduct() {
    if (m_products.empty())
    {
        cout << "No Products to Remove.\n";
        return;
    }
    listProducts();
    int productId;
    cout << "Enter Product ID to remove: ";
    cin >> productId;
    for (auto it = m_products.begin(); it != m_products.end(); ++it)
    {
        if ((*it)->getProductId() == productId)
        {
            (*it)->updateStatus("Removed");
            cout << "Product with ID " << (*it)->getProductName() << " removed successfully.\n";
            saveSystem();
            return;
        }
    }
    cout << "Error: Product with ID " << productId << " not found.\n";
}

void WarehouseController::removeVehicle() {
    if (m_vehicles.empty())
    {
        cout << "No Vehicles to Remove\n";
        return;
    }
    listVehicles();
    int vehicleId;
    cout << "Enter Vehicle ID to remove: ";
    cin >> vehicleId;
    for (auto it = m_vehicles.begin(); it != m_vehicles.end(); ++it)
    {
        if ((*it)->getVehicleId() == vehicleId)
        {
            (*it)->setStatus("Removed");
            (*it)->setIsAvailable(false);
            cout << "Vehicle with ID " << vehicleId << " removed successfully.\n";
            return;
        }
    }
    cout << "Error: Vehicle with ID " << vehicleId << " not found.\n";
}

void WarehouseController::removeStore() {
    if (m_stores.empty())
    {
        cout << "No Store to Remove.\n";
        return;
    }
    listStores();
    int storeId;
    cout << "Enter Store ID to remove: ";
    cin >> storeId;
    for (auto it = m_stores.begin(); it != m_stores.end(); ++it)
    {
        if ((*it)->getStoreId() == storeId)
        {
            (*it)->setStoreStatus("Removed");
            cout << "Store with ID " << (*it)->getStoreName() << " removed successfully.\n";
            return;
        }
    }
    cout << "Error: Store with ID " << storeId << " not found.\n";
}

void WarehouseController::performQualityCheck() {
    if (m_dispatchPendingProduct.empty())
    {
        cout << "No items pending quality check.\n";
        return;
    }
    for (vector<DeliveryItem>::iterator it = m_dispatchPendingProduct.begin(); it != m_dispatchPendingProduct.end(); )
    {
        shared_ptr<Product> product = it->getProduct();
        if (product->getQualityScore() >= m_qualityCheck.getThreshold())
        {
            product->updateStatus("Approved");
            ++it;
        }
        else
        {
            product->updateStatus("Damaged");
            m_damagedProducts.push_back(*it);
            it = m_dispatchPendingProduct.erase(it);
        }
    }
    saveSystem();
}

void WarehouseController::loadSystem()
{
    fileManager.loadVector(m_products, "Product.txt");
    fileManager.loadVector(m_vehicles, "Vehicle.txt");
    fileManager.loadVector(m_stores, "Store.txt");
    fileManager.loadVector(m_users, "User.txt");
    fileManager.loadDeliveries(m_deliveries, m_stores, m_vehicles, m_products, "Delivery.txt");
    fileManager.loadDispatchQueue(m_dispatchPendingProduct, m_products, m_stores, "DispatchPendingItems.txt");
    fileManager.loadRejectedItems(m_damagedProducts, m_products, m_stores, "DamagedProduct.txt");
}

void WarehouseController::saveSystem()
{
    fileManager.saveVector(m_products, "Product.txt");
    fileManager.saveVector(m_vehicles, "Vehicle.txt");
    fileManager.saveVector(m_stores, "Store.txt");
    fileManager.saveVector(m_users, "User.txt");
    fileManager.saveDeliveries(m_deliveries, "Delivery.txt");
    fileManager.saveDispatchQueue(m_dispatchPendingProduct, "DispatchPendingItems.txt");
    fileManager.saveRejectedItems(m_damagedProducts, "DamagedProduct.txt");
}

std::vector<std::shared_ptr<Product>>& WarehouseController::getProducts()
{
    return m_products;
}

std::vector<std::shared_ptr<User>>& WarehouseController::getUsers()
{
    return m_users;
}

std::vector<std::shared_ptr<Vehicle>>& WarehouseController::getVehicles()
{
    return m_vehicles;
}

std::vector<std::shared_ptr<Store>>& WarehouseController::getStores()
{
    return m_stores;
}