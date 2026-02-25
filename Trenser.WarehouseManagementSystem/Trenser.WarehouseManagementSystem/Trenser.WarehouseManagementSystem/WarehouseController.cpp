using namespace std;
#include "WarehouseController.h"
#include "Manager.h"
#include "Staff.h"

const std::string WarehouseController::PRODUCT_FILE = "Product.txt";
const std::string WarehouseController::VEHICLE_FILE = "Vehicle.txt";
const std::string WarehouseController::STORE_FILE = "Store.txt";
const std::string WarehouseController::USER_FILE = "User.txt";
const std::string WarehouseController::DELIVERY_FILE = "Delivery.txt";
const std::string WarehouseController::DISPATCH_FILE = "DispatchPendingItems.txt";
const std::string WarehouseController::DAMAGED_FILE = "DamagedProduct.txt";

void WarehouseController::controllerMenu() {
    int choice;
    do
    {
        try
        {
            cout << "\n=========WareHouse Management===========\n";
            cout << "1. Login\n2. Exit\n\nEnter the choice : ";
            readValue<int>(choice);
            switch (choice)
            {
            case 1:
                loginUser();
                break;
            case 2:
                saveSystem();
                cout << "Exiting.....";
                break;
            default:
                cout << "Invalid Input. Try again\n";
                break;
            }
        }
        catch (const exception& e)
        {
            cout << "Error: " << e.what() << "\n" << "\n";
        }
    } while (choice != 2);
}

string getProductStatusString(ProductStatus status)
{
    switch (status)
    {
    case ProductStatus::ACTIVE:
        return "Active";
    case ProductStatus::APPROVED:
        return "Approved";
    case ProductStatus::DAMAGED:
        return "Damaged";
    case ProductStatus::OUT_OF_STOCK:
        return "Out of Stock";
    case ProductStatus::REMOVED:
        return "Removed";
    default:
        return "Invalid Product Status";
    }
}

string getDeliveryStatusString(DeliveryStatus status)
{
    switch (status)
    {
    case DeliveryStatus::PENDING_DISPATCH:
        return "Pending Dispatch";
    case DeliveryStatus::IN_TRANSIT:
        return "In Transit";
    case DeliveryStatus::DELIVERED:
        return "Delivered";
    default:
        return "Invalid Delivery Status";
    }
}

bool WarehouseController::authorizeUser(const string& username, const string& password)
{
    try
    {
        for (auto iterator = m_users.begin(); iterator != m_users.end(); ++iterator)
        {
            if ((*iterator)->getUserName() == username && (*iterator)->getPassword() == password)
            {
                m_autherizedUser = (*iterator);
                return true;
            }
        }
        return false;
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << "\n" << "\n";
        return false;
    }
}

void WarehouseController::loginUser() {
    string username, password;
    try {
        cout << "Username : ";
        readString(username);
        cout << "Password : ";
        readString(password);
        if (authorizeUser(username, password))
        {
            cout << "Login Successfull ! Welcome " << m_autherizedUser->getUserName() << endl;
            if (m_autherizedUser->getRole() == "Admin")
            {
                m_menu = make_unique<AdminMenu>();
            }
            else if (m_autherizedUser->getRole() == "Manager")
            {
                m_menu = make_unique<ManagerMenu>();
            }
            else if (m_autherizedUser->getRole() == "Staff")
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
                cout << "\nError: No menu available for role '" << m_autherizedUser->getRole() << "'\n";
            }
        }
        else
        {
            cout << "Invalid Credentials.Try Again\n";
        }
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << "\n" << "\n";
    }
}

void WarehouseController::addUser() {
    string username, password, role;
    int roleChoice;
    try
    {
        cout << "Enter the Username: ";
        readString(username);
        cout << "Enter Password: ";
        readString(password);
        cout << "Select Role:\n1. Manager\n2. Staff\n\nEnter choice: ";
        readValue<int>(roleChoice);
        shared_ptr<User> newUser;
        int userId = static_cast<int>(m_users.size()) + 101;
        switch (roleChoice)
        {
        case 1: role = "Manager";
            newUser = make_shared<Manager>(userId, username, password);
            break;
        case 2: role = "Staff";
            newUser = make_shared<Staff>(userId, username, password);
            break;
        default: cout << "Invalid Input.\n";
            return;
        }
        for (auto iterator = m_users.begin(); iterator != m_users.end(); ++iterator)
        {
            if ((*iterator)->getUserName() == username)
            {
                cout << "Error: Username '" << username << "' already exists.\n";
                return;
            }
        }
        m_users.push_back(newUser);
        cout << "User '" << username << "' registered successfully as " << role << ".\n";
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << "\n" << "\n";
    }
}

void WarehouseController::addVehicle()
{
    int capacity, availabilityInput;
    string driverName;
    bool isAvailable;
    try
    {
        cout << "Enter the Capacity: ";
        readValue<int>(capacity);
        cout << "Enter the Driver Name: ";
        readString(driverName);
        cout << "Is the Car Available for Delivery: \n1. Available\n2. Not Available\nEnter Your choice : ";
        readValue<int>(availabilityInput);
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
        for (auto iterator = m_vehicles.begin(); iterator != m_vehicles.end(); ++iterator)
        {
            if ((*iterator)->getVehicleId() == vehicleId)
            {
                throw runtime_error("Vehicle ID already exists.");
            }
        }
        shared_ptr<Vehicle> newVehicle = make_shared<Vehicle>(vehicleId, driverName, capacity, isAvailable);
        m_vehicles.push_back(newVehicle);
        cout << "Vehicle '" << vehicleId << "' added successfully.\n";
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << "\n" << "\n";
    }
}

void WarehouseController::addProduct()
{
    try
    {
        int productId, qualityScore, stockQuantity;
        string productName;
        cout << "Enter the Product Name : ";
        readString(productName);
        cout << "Enter the Stock quantity : ";
        readValue<int>(stockQuantity);
        cout << "Enter the Quality score(0 - 10) : ";
        readValue<int>(qualityScore);
        if (qualityScore > 10 || qualityScore < 0)
        {
            cout << "Invalid quality score. Enter a number between (0 - 10)\n";

        }
        productId = static_cast<int>(m_products.size()) + 101;
        for (auto it = m_products.begin(); it != m_products.end(); ++it)
        {
            if ((*it)->getProductId() == productId)
            {
                cout << "Product ID already exists.\n";
                return;
            }
        }
        shared_ptr<Product> newProduct = make_shared<Product>(productId, productName, stockQuantity, qualityScore);
        m_products.push_back(newProduct);
        cout << "Product '" << productName << "' added successfully.\n";
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << "\n" << "\n";
    }
}

void WarehouseController::addStore()
{
    try
    {
        int storeId;
        string storeName, location;
        cout << "Enter the Store Name : ";
        readString(storeName);
        cout << "Enter the Store Location : ";
        readString(location);
        storeId = static_cast<int>(m_stores.size()) + 101;
        for (auto iterator = m_stores.begin(); iterator != m_stores.end(); ++iterator)
        {
            if ((*iterator)->getStoreId() == storeId)
            {
                throw runtime_error("Store ID already exists.");
            }
        }
        shared_ptr<Store> newStore = make_shared<Store>(storeId, storeName, location);
        m_stores.push_back(newStore);
        cout << "Store '" << storeName << "' added successfully.\n";
        saveSystem();
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << "\n";
    }
}


shared_ptr<Product> WarehouseController::selectProduct(int productId) 
{
    for (auto& product : m_products)
    {
        if (product->getProductId() == productId && product->getStatus() != ProductStatus::REMOVED) 
        {
            return product;
        }
    }
    return nullptr;
}

shared_ptr<Store> WarehouseController::selectStore(int storeId) 
{
    for (auto& store : m_stores) 
    {
        if (store->getStoreId() == storeId && store->isActive()) 
        {
            return store;
        }
    }
    return nullptr;
}

bool WarehouseController::validateStock(shared_ptr<Product> product, int quantity) 
{
    if (product->getStockQuantity() < quantity)
    {
        cout << "Error: Not enough stock for Product '" << product->getProductId() << "'.\n";
        return false;
    }
    return true;
}

void WarehouseController::queueDispatch(shared_ptr<Product> product, shared_ptr<Store> store, int quantity) 
{
    DeliveryItem item(quantity, product, store);
    m_dispatchPendingProduct.push_back(item);
    product->updateStock(-quantity);
    if (product->getStockQuantity() == 0)
    {
        product->updateStatus(ProductStatus::OUT_OF_STOCK);
    }
    cout << "Product '" << product->getProductName() << "' queued for quality check before dispatch to Store '" << store->getStoreName() << "'.\n";
}

void WarehouseController::addToDispatchQueue() {
    try 
    {
        if (m_products.empty()) 
        {
            cout << "No product available to assign.\n";
            return;
        }
        listProducts();
        int productId;
        cout << "Enter the Product Id: ";
        readValue<int>(productId);
        auto selectedProduct = selectProduct(productId);
        if (!selectedProduct)
        {
            cout << "Error: Product '" << productId << "' not found.\n";
            return;
        }
        if (m_stores.empty()) 
        {
            cout << "No stores available to assign.\n";
            return;
        }
        listStores();
        int storeId;
        cout << "Enter the Store Id: ";
        readValue<int>(storeId);
        auto selectedStore = selectStore(storeId);
        if (!selectedStore) {
            cout << "Error: Store '" << storeId << "' not found.\n";
            return;
        }
        int quantity;
        cout << "Enter the Quantity: ";
        readValue<int>(quantity);
        if (!validateStock(selectedProduct, quantity)) 
        {
            return;
        }
        queueDispatch(selectedProduct, selectedStore, quantity);
    }
    catch (const exception& e) 
    {
        cout << e.what() << "\n";
    }
}

void WarehouseController::listUsers() const 
{
    try
    {
        if (m_users.empty())
        {
            cout << "No users registered.\n";
            return;
        }
        cout << "--- User List ---\n";
        for (auto iterator = m_users.begin(); iterator != m_users.end(); ++iterator)
        {
            if (!(*iterator)->isActive())
            {
                continue;
            }
            cout << "User ID: " << (*iterator)->getUserId() << " | Username: " << (*iterator)->getUserName() 
                << " | Role: " << (*iterator)->getRole() << " | Status: " << ((*iterator)->isActive() ? "Active" : "Removed") << "\n";

        }
    }
    catch (const exception& e)
    {
        cout << e.what() << "\n";
    }
}

void WarehouseController::listVehicles() const 
{
    try
    {
        if (m_vehicles.empty())
        {
            cout << "No vehicles available.\n";
            return;
        }
        cout << "--- Vehicle List ---\n";
        for (auto iterator = m_vehicles.begin(); iterator != m_vehicles.end(); ++iterator)
        {
            if (!(*iterator)->isActive())
            {
                continue;
            }
            cout << "Vehicle ID: " << (*iterator)->getVehicleId() << " | Driver: " << (*iterator)->getdriverName()
                << " | Capacity: " << (*iterator)->getcapacity()<< " | Available: " << ((*iterator)->getIsAvailable() ? "Yes" : "No") << "\n";
        }
    }
    catch (const exception& e)
    {
        cout << e.what() << "\n";
    }
}

void WarehouseController::listProducts() const
{
    try
    {
        if (m_products.empty())
        {
            cout << "No products available in the warehouse.\n";
            return;
        }
        cout << "\n--- Product List ---\n";
        for (auto iterator = m_products.begin(); iterator != m_products.end(); ++iterator)
        {
            if ((*iterator)->getStatus() == ProductStatus::REMOVED || (*iterator)->getStatus() == ProductStatus::OUT_OF_STOCK)
            {
                continue;
            }
            cout << "Product ID: " << (*iterator)->getProductId() << " | Name: " << (*iterator)->getProductName() << " | Stock: " << (*iterator)->getStockQuantity()
                << " | Quality Score: " << (*iterator)->getQualityScore() << " | Status: " << getProductStatusString((*iterator)->getStatus()) << "\n";
        }
    }
    catch (const exception& e)
    {
        cout << e.what() << "\n";
    }
}

void WarehouseController::listStores() const 
{
    try
    {
        if (m_stores.empty())
        {
            cout << "No stores registered.\n";
            return;
        }
        cout << "--- Store List ---\n";
        for (auto iterator = m_stores.begin(); iterator != m_stores.end(); ++iterator)
        {
            if (!(*iterator)->isActive())
            {
                continue;
            }
            cout << "Store ID: " << (*iterator)->getStoreId() << " | Name: " << (*iterator)->getStoreName()
                << " | Location: " << (*iterator)->getStoreLocation() << "\n";
        }
    }
    catch (const exception& e)
    {
        cout << e.what() << "\n";
    }
}

void WarehouseController::listDispatchPendingItems() const 
{
    try
    {
        if (m_dispatchPendingProduct.empty())
        {
            cout << "No items pending to dispatch.\n";
            return;
        }
        cout << "--- Dispatch Pending Items ---\n";
        for (auto iterator = m_dispatchPendingProduct.begin(); iterator != m_dispatchPendingProduct.end(); ++iterator)
        {
            shared_ptr<Product> product = iterator->getProduct();
            if (product)
            {
                cout << "Product ID: " << product->getProductId() << " | Name: " << product->getProductName()
                    << " | Quantity: " << iterator->getQuantity() << " | Status: " << getProductStatusString(product->getStatus()) << "\n";
            }
        }
    }
    catch (const exception& e)
    {
        cout << e.what() << "\n";
    }
}

bool WarehouseController::hasPendingItem() const
{
    return !m_dispatchPendingProduct.empty();
}

map<shared_ptr<Store>, vector<DeliveryItem>> WarehouseController::groupItemsByStore() const
{
    map<shared_ptr<Store>, vector<DeliveryItem>> storeGroups;
    for (const auto& item : m_dispatchPendingProduct) 
    {
        if (item.getProduct()->getStatus() == ProductStatus::APPROVED) 
        {
            storeGroups[item.getStore()].push_back(item);
        }
    }
    return storeGroups;
}

Delivery WarehouseController::createDeliveryForStore(const shared_ptr<Store>& store, const vector<DeliveryItem>& items)
{
    int deliveryId = static_cast<int>(m_deliveries.size()) + 101;
    Delivery newDelivery(deliveryId, store->getStoreLocation(), store, nullptr);
    for (const auto& item : items)
    {
        newDelivery.getItems().push_back(item);
    }
    return newDelivery;
}

shared_ptr<Vehicle> WarehouseController::selectVehicleForStore(const shared_ptr<Store>& store) 
{
    int vehicleId;
    listVehicles();
    cout << "Enter Vehicle ID to assign for Store " << store->getStoreLocation() << ": ";
    readValue<int>(vehicleId);
    for (auto& vehicle : m_vehicles)
    {
        if (vehicle->getVehicleId() == vehicleId && vehicle->getIsAvailable() && vehicle->isActive())
        {
            vehicle->setIsAvailable(false);
            return vehicle;
        }
    }
    cout << "Vehicle not available. Skipping store.\n";
    return nullptr;
}

void WarehouseController::	confirmAndSaveDelivery(Delivery& delivery, const shared_ptr<Vehicle>& vehicle) 
{
    delivery.assignVehicle(vehicle);
    delivery.updateDeliveryStatus(DeliveryStatus::IN_TRANSIT);
    m_deliveries.push_back(delivery);
    cout << "Delivery " << delivery.getDeliveryId() << " created for Store " << delivery.getStore()->getStoreLocation() << "\n";
}

void WarehouseController::removeApprovedItemsFromQueue() 
{
    m_dispatchPendingProduct.erase(
        remove_if(m_dispatchPendingProduct.begin(), m_dispatchPendingProduct.end(),
            [](const DeliveryItem& item) {
                return item.getProduct()->getStatus() == ProductStatus::APPROVED;
            }),
        m_dispatchPendingProduct.end()
    );
}

void WarehouseController::dispatchDelivery()
{
    try
    {
        if (!hasPendingItem())
        {
            cout << "No items pending delivery.\n";
            cout << "No items pending delivery.\n";
            return;
        }
        auto storeGroups = groupItemsByStore();
        for (auto& storeGroup : storeGroups)
        {
            shared_ptr<Store> store = storeGroup.first;  
            vector<DeliveryItem>& items = storeGroup.second; 

            Delivery newDelivery = createDeliveryForStore(store, items); 
            auto vehicle = selectVehicleForStore(store);           
            if (!vehicle)
            {
                continue;
            }
            confirmAndSaveDelivery(newDelivery, vehicle);
        }
    }
    catch (const exception& e)
    {
        cout << e.what() << "\n";
    }
}


void WarehouseController::updateDeliveryStatus()
{
    int deliveryId;
    try
    {
        listDeliveries();
        cout << "Enter Delivery ID to update: ";
        readValue<int>(deliveryId);
        for (vector<Delivery>::iterator iterator = m_deliveries.begin(); iterator != m_deliveries.end(); ++iterator)
        {
            if (iterator->getDeliveryId() == deliveryId)
            {
                string currentStatus = getDeliveryStatusString(iterator->getDeliveryStatus());
                cout << "Current status: " << currentStatus << "\n";
                int choice;
                cout << "Select new status:\n";
                cout << "1. Dispatched\n";
                cout << "2. In Transit\n";
                cout << "3. Delivered\nSelect your Choice : ";
                cin >> choice;
                if (currentStatus == "Delivered")
                {
                    cout << "Error: Delivery is already completed and cannot be changed.\n";
                    return;
                }
                if (currentStatus == "In Transit" && choice == 1)
                {
                    cout << "Error: Cannot change status from In Transit back to Dispatched.\n";
                    return;
                }
                switch (choice)
                {
                case 1:
                    iterator->updateDeliveryStatus(DeliveryStatus::PENDING_DISPATCH);
                    break;
                case 2:
                    iterator->updateDeliveryStatus(DeliveryStatus::IN_TRANSIT);
                    break;
                case 3:
                    iterator->updateDeliveryStatus(DeliveryStatus::DELIVERED);
                    if (iterator->getVehicle())
                    {
                        iterator->getVehicle()->setIsAvailable(true);
                    }
                    break;
                default:
                    cout << "Invalid status choice.\n";
                    return;
                }
                cout << "Delivery " << deliveryId << " status updated successfully.\n";
                return;
            }
        }
        cout << "Error: Delivery with ID " << deliveryId << " not found.\n";
    }
    catch (const exception& e)
    {
        cout << e.what() << "\n";
    }
}

void WarehouseController::listDeliveries() const
{
    try
    {
        if (m_deliveries.empty())
        {
            cout << "No deliveries available.\n";
            return;
        }
        for (vector<Delivery>::const_iterator iterator = m_deliveries.begin(); iterator != m_deliveries.end(); ++iterator)
        {
            cout << "-----------------------------------------------------\n";
            cout << "\nDelivery ID: " << iterator->getDeliveryId() << " | Status: " << getDeliveryStatusString(iterator->getDeliveryStatus()) << " | Address: " << iterator->getDeliveryAddress() << "\n";
            shared_ptr<Store> store = iterator->getStore();
            if (store)
            {
                cout << "Store ID: " << store->getStoreId() << " | Store Name: " << store->getStoreName() << " | Location: " << store->getStoreLocation() << "\n";
            }
            shared_ptr<Vehicle> vehicle = iterator->getVehicle();
            if (vehicle)
            {
                cout << "Vehicle ID: " << vehicle->getVehicleId() << " | Driver Name: " << vehicle->getdriverName() << " | Available: " << (vehicle->getIsAvailable() ? "Yes" : "No") << "\n";
            }
            cout << "\nItems:\n";
            const vector<DeliveryItem>& items = iterator->getItems();
            for (vector<DeliveryItem>::const_iterator itemIterator = items.begin(); itemIterator != items.end(); ++itemIterator)
            {
                shared_ptr<Product> product = itemIterator->getProduct();
                if (product)
                {
                    cout << "Product ID: " << product->getProductId() << " | Name: " << product->getProductName() << " | Quantity: " << itemIterator->getQuantity() << "\n";
                }
            }
            cout << "-----------------------------------\n";
        }
    }
    catch (const exception& e)
    {
        cout << e.what() << "\n";
    }
}

void WarehouseController::removeUser()
{
    try
    {
        if (m_users.empty())
        {
            cout << "No user to Remove.\n";
            return;
        }
        listUsers();
        int userId;
        cout << "Enter User ID to remove: ";
        readValue<int>(userId);
        for (auto iterator = m_users.begin(); iterator != m_users.end(); ++iterator)
        {
            if ((*iterator)->getUserId() == userId && (*iterator)->getRole() != "Admin")
            {
                (*iterator)->setIsActive(false);
                cout << "User '" << (*iterator)->getUserName() << "' removed successfully.\n";
                return;
            }
        }
        cout << "Error: User with ID " << userId << " not found.\n";
    }
    catch (const exception& e)
    {
        cout << e.what() << "\n";
    }
}

void WarehouseController::removeProduct() 
{
    try
    {
        if (m_products.empty())
        {
            cout << "No Products to Remove.\n";
            return;
        }
        listProducts();
        int productId;
        cout << "Enter Product ID to remove: ";
        readValue<int>(productId);
        for (auto iterator = m_products.begin(); iterator != m_products.end(); ++iterator)
        {
            if ((*iterator)->getProductId() == productId)
            {
                (*iterator)->updateStatus(ProductStatus::REMOVED);
                cout << "Product '" << (*iterator)->getProductName() << "' removed successfully.\n";
                return;
            }
        }
        cout << "Error: Product with ID " << productId << " not found.\n";
    }
    catch (const exception& e)
    {
        cout << e.what() << "\n";
    }
}

void WarehouseController::removeVehicle()
{
    try
    {
        if (m_vehicles.empty())
        {
            cout << "No Vehicles to Remove\n";
            return;
        }
        listVehicles();
        int vehicleId;
        cout << "Enter Vehicle ID to remove: ";
        readValue<int>(vehicleId);
        for (auto iterator = m_vehicles.begin(); iterator != m_vehicles.end(); ++iterator)
        {
            if ((*iterator)->getVehicleId() == vehicleId)
            {
                (*iterator)->setIsActive(false);
                (*iterator)->setIsAvailable(false);
                cout << "Vehicle with ID " << vehicleId << " removed successfully.\n";
                return;
            }
        }
        cout << "Error: Vehicle with ID " << vehicleId << " not found.\n";
    }
    catch (const exception& e)
    {
        cout << e.what() << "\n";
    }
}

void WarehouseController::removeStore() 
{
    try
    {
        if (m_stores.empty())
        {
            cout << "No Store to Remove.\n";
            return;
        }
        listStores();
        int storeId;
        cout << "Enter Store ID to remove: ";
        readValue<int>(storeId);
        for (auto iterator = m_stores.begin(); iterator != m_stores.end(); ++iterator)
        {
            if ((*iterator)->getStoreId() == storeId)
            {
                (*iterator)->setIsActive("Removed");
                cout << "Store '" << (*iterator)->getStoreName() << "' removed successfully.\n";
                return;
            }
        }
        cout << "Error: Store with ID " << storeId << " not found.\n";
    }
    catch (const exception& e)
    {
        cout << e.what() << "\n";
    }
}

void WarehouseController::performQualityCheck()
{
    try
    {
        if (m_dispatchPendingProduct.empty())
        {
            cout << "No items pending quality check.\n";
            return;
        }
        for (vector<DeliveryItem>::iterator iterator = m_dispatchPendingProduct.begin(); iterator != m_dispatchPendingProduct.end(); )
        {
            shared_ptr<Product> product = iterator->getProduct();
            if (product->getQualityScore() >= m_qualityCheck.getThreshold())
            {
                product->updateStatus(ProductStatus::APPROVED);
                ++iterator;
            }
            else
            {
                product->updateStatus(ProductStatus::DAMAGED);
                m_damagedProducts.push_back(*iterator);
                iterator = m_dispatchPendingProduct.erase(iterator);
            }
        }
        cout << "Quality Checked Completed.\n";
    }
    catch (const exception& e)
    {
        cout << e.what() << "\n";
    }
}

void WarehouseController::loadSystem()
{
    fileManager.loadVector(m_products, PRODUCT_FILE);
    fileManager.loadVector(m_vehicles, VEHICLE_FILE);
    fileManager.loadVector(m_stores, STORE_FILE);
    fileManager.loadVector(m_users, USER_FILE);
    fileManager.loadDeliveries(m_deliveries, m_stores, m_vehicles, m_products, DELIVERY_FILE);
    fileManager.loadDispatchQueue(m_dispatchPendingProduct, m_products, m_stores, DISPATCH_FILE);
    fileManager.loadRejectedItems(m_damagedProducts, m_products, m_stores, DAMAGED_FILE);
}

void WarehouseController::saveSystem()
{
    fileManager.saveVector(m_products, PRODUCT_FILE);
    fileManager.saveVector(m_vehicles, VEHICLE_FILE);
    fileManager.saveVector(m_stores, STORE_FILE);
    fileManager.saveVector(m_users, USER_FILE);
    fileManager.saveDeliveries(m_deliveries, DELIVERY_FILE);
    fileManager.saveDispatchQueue(m_dispatchPendingProduct, DISPATCH_FILE);
    fileManager.saveRejectedItems(m_damagedProducts, DAMAGED_FILE);
}

vector<shared_ptr<Product>>& WarehouseController::getProducts()
{
    return m_products;
}

vector<shared_ptr<User>>& WarehouseController::getUsers()
{
    return m_users;
}

vector<shared_ptr<Vehicle>>& WarehouseController::getVehicles()
{
    return m_vehicles;
}

vector<shared_ptr<Store>>& WarehouseController::getStores()
{
    return m_stores;
}