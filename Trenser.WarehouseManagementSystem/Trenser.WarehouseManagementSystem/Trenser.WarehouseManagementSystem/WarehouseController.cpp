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

bool WarehouseController::authorizeUser(const string& username, const string& password)
{
    try
    {
        for (auto iterator = m_users.begin(); iterator != m_users.end(); ++iterator)
        {
            if ((*iterator)->getUserName() == username && (*iterator)->getPassword() == password)
            {
                m_autherizedUser = *(*iterator);
                return true;
            }
        }
        return false;
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << "\n" << "\n";
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
        switch (roleChoice)
        {
        case 1: role = "Manager";
            break;
        case 2: role = "Staff";
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
        int userId = static_cast<int>(m_users.size()) + 101;
        shared_ptr<User> newUser = make_shared<User>(userId, username, password, role);
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

void WarehouseController::dispatchProduct() {
    int productId, storeId, quantity;
    shared_ptr<Product> selectedProduct = nullptr;
    shared_ptr<Store> selectedStore = nullptr;
    try
    {
        if (m_products.empty())
        {
            cout << "No product available to assign.\n";
            return;
        }
        listProducts();
        cout << "Enter the Product Id: ";
        readValue<int>(productId);
        for (auto productIterator = m_products.begin(); productIterator != m_products.end(); ++productIterator)
        {
            if ((*productIterator)->getProductId() == productId && (*productIterator)->getStatus() != "Removed")
            {
                selectedProduct = *productIterator;
                break;
            }
        }
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
        cout << "Enter the Store Id: ";
        readValue<int>(storeId);
        for (auto storeIterator = m_stores.begin(); storeIterator != m_stores.end(); ++storeIterator)
        {
            if ((*storeIterator)->getStoreId() == storeId && (*storeIterator)->getStoreStatus() != "Removed")
            {
                selectedStore = *storeIterator;
                break;
            }
        }
        if (!selectedStore)
        {
            cout << "Error: Store '" << storeId << "' not found.\n";
            return;
        }
        cout << "Enter the Quantity: ";
        readValue<int>(quantity);
        if (selectedProduct->getStockQuantity() < quantity)
        {
            cout << "Error: Not enough stock for Product '" << productId << "'.\n";
            return;
        }
        selectedProduct->updateStock(-quantity);
        if (selectedProduct->getStockQuantity() == 0)
        {
            selectedProduct->updateStatus("Out of Stock");
        }
        DeliveryItem item(quantity, selectedProduct, selectedStore);
        m_dispatchPendingProduct.push_back(item);
        cout << "Product '" << selectedProduct->getProductName() << "' queued for quality check before dispatch to Store '" << selectedStore->getStoreName() << "'.\n";
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
            if ((*iterator)->getUserStatus() == "Removed")
            {
                continue;
            }
            cout << "User ID: " << (*iterator)->getUserId()
                << " | Username: " << (*iterator)->getUserName()
                << " | Role: " << (*iterator)->getRole()
                << " | Status: " << (*iterator)->getUserStatus()
                << "\n";
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
            if ((*iterator)->getStatus() != "Active")
            {
                continue;
            }
            cout << "Vehicle ID: " << (*iterator)->getVehicleId()
                << " | Driver: " << (*iterator)->getdriverName()
                << " | Capacity: " << (*iterator)->getcapacity()
                << " | Available: " << ((*iterator)->getIsAvailable() ? "Yes" : "No")
                << "\n";
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
            if ((*iterator)->getStatus() == "Removed")
            {
                continue;
            }
            cout << "Product ID: " << (*iterator)->getProductId()
                << " | Name: " << (*iterator)->getProductName()
                << " | Stock: " << (*iterator)->getStockQuantity()
                << " | Quality Score: " << (*iterator)->getQualityScore()
                << " | Status: " << (*iterator)->getStatus()
                << "\n";
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
            if ((*iterator)->getStoreStatus() == "Removed")
            {
                continue;
            }
            cout << "Store ID: " << (*iterator)->getStoreId()
                << " | Name: " << (*iterator)->getStoreName()
                << " | Location: " << (*iterator)->getStoreLocation()
                << "\n";
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
                cout << "Product ID: " << product->getProductId()
                    << " | Name: " << product->getProductName()
                    << " | Quantity: " << iterator->getQuantity()
                    << " | Status: " << product->getStatus()
                    << "\n";
            }
        }
    }
    catch (const exception& e)
    {
        cout << e.what() << "\n";
    }
}

void WarehouseController::acceptDelivery()
{
    int deliveryId, vehicleId;
    shared_ptr<Vehicle> selectedVehicle = nullptr;
    try
    {
        if (m_dispatchPendingProduct.empty())
        {
            cout << "No items pending delivery.\n";
            return;
        }
        map<shared_ptr<Store>, vector<DeliveryItem>> storeGroups;
        for (auto iterator = m_dispatchPendingProduct.begin(); iterator != m_dispatchPendingProduct.end(); ++iterator)
        {
            storeGroups[iterator->getStore()].push_back(*iterator);
        }
        for (auto storeIterator = storeGroups.begin(); storeIterator != storeGroups.end(); ++storeIterator)
        {
            shared_ptr<Store> store = storeIterator->first;
            vector<DeliveryItem>& items = storeIterator->second;
            deliveryId = static_cast<int>(m_deliveries.size()) + 1;
            shared_ptr<Vehicle> nullVehicle = nullptr;
            Delivery newDelivery(deliveryId, store->getStoreLocation(), store, nullVehicle);
            for (auto itemIterator = items.begin(); itemIterator != items.end(); ++itemIterator)
            {
                newDelivery.getItems().push_back(*itemIterator);
            }
            listVehicles();
            cout << "Enter Vehicle ID to assign for Store " << store->getStoreLocation() << ": ";
            readValue<int>(vehicleId);
            for (auto vehicleIterator = m_vehicles.begin(); vehicleIterator != m_vehicles.end(); ++vehicleIterator)
            {
                if ((*vehicleIterator)->getVehicleId() == vehicleId && (*vehicleIterator)->getIsAvailable() && (*vehicleIterator)->getStatus() == "Active")
                {
                    (*vehicleIterator)->setIsAvailable(false);
                    selectedVehicle = *vehicleIterator;
                    break;
                }
            }
            if (!selectedVehicle)
            {
                cout << "Vehicle not available. Skipping store.\n";
                continue;
            }
            newDelivery.assignVehicle(selectedVehicle);
            newDelivery.updateDeliveryStatus("In Transit");
            m_deliveries.push_back(newDelivery);
            cout << "Delivery " << deliveryId << " created for Store " << store->getStoreLocation() << "\n";
        }
        m_dispatchPendingProduct.clear();
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
                string currentStatus = iterator->getDeliveryStatus();
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
                    iterator->updateDeliveryStatus("Dispatched");
                    break;
                case 2:
                    iterator->updateDeliveryStatus("In Transit");
                    break;
                case 3:
                    iterator->updateDeliveryStatus("Delivered");
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
            cout << "\nDelivery ID: " << iterator->getDeliveryId() << " | Status: " << iterator->getDeliveryStatus() << " | Address: " << iterator->getDeliveryAddress() << "\n";
            shared_ptr<Store> store = iterator->getStore();
            if (store)
            {
                cout << "\nStore ID: " << store->getStoreId() << " | Store Name: " << store->getStoreName() << " | Location: " << store->getStoreLocation() << "\n";
            }
            shared_ptr<Vehicle> vehicle = iterator->getVehicle();
            if (vehicle)
            {
                cout << "\nVehicle ID: " << vehicle->getVehicleId() << " | Driver Name: " << vehicle->getdriverName() << " | Available: " << (vehicle->getIsAvailable() ? "Yes" : "No") << "\n";
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
                (*iterator)->updateUserStatus("Removed");
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
                (*iterator)->updateStatus("Removed");
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
                (*iterator)->setStatus("Removed");
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
                (*iterator)->setStoreStatus("Removed");
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
                product->updateStatus("Approved");
                ++iterator;
            }
            else
            {
                product->updateStatus("Damaged");
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