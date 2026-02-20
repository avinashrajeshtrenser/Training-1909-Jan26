#include <iostream>
using namespace std;
#include "WarehouseController.h"
void WarehouseController::controllerMenu()
{
	int choice;
	do 
	{
		cout << "\n=========WareHouse Management===========\n";
		cout << "1. Register\n2. Login\n3. Exit\n\nEnter the choice : ";
		cin >> choice;
		string username, password, role;
		switch (choice)
		{
		case 1: addUser();
			break;
		case 2: loginUser();
			break;
		case 3: exit(0);
		default: cout << "Invalid Input. Try again\n";
		}
	} while (choice != 3);
}
void WarehouseController::loginUser()
{
	string username, password, role;
	cout << "Username : ";
	cin >> username;
	cout << "Password : ";
	cin >> password;
	if (authorizeUser(username, password))
	{
		cout << "Login Successfull ! Welcome " << m_autherizedUser.getUserName() << endl;
		if (m_autherizedUser.getRole() == "Admin")
		{
			m_menu = new AdminMenu();
		}
		else if (m_autherizedUser.getRole() == "Manager")
		{
			m_menu = new ManagerMenu();
		}
		else if (m_autherizedUser.getRole() == "Staff")
		{
			m_menu = new StaffMenu();
		}
		if (m_menu != nullptr)
		{
			m_menu->handleOperation(*this);
		}
		else
		{
			cout << "\nError: No menu available for role '"
				<< m_autherizedUser.getRole() << "'\n";
		}
	}
	else
	{
		cout << "Invalid Credentials.Try Again\n";
	}
}
bool WarehouseController::authorizeUser(const string& username, const string& password)
{
    for (auto it = m_users->begin(); it != m_users->end(); ++it)
    {
        if (it->getUserName() == username && it->getPassword() == password)
        {
            m_autherizedUser = *it;
            return true;
        }
    }
    return false;
}
void WarehouseController::addUser()
{
    string username, password, role;
    cout << "Enter the Username : ";
    cin >> username;
    cout << "Enter Password : ";
    cin >> password;
    cout << "Enter the role (Manager, Staff): ";
    cin >> role;
    User newUser(m_users->size() + 1, username, password, role);
    for (auto it = m_users->begin(); it != m_users->end(); ++it)
    {
        if (it->getUserName() == username)
        {
            cout << "Error: Username '" << username << "' already exists.\n";
            return;
        }
    }
    m_users->push_back(newUser);
    cout << "User '" << username << "' registered successfully.\n";
}
void WarehouseController::addVehicle()
{
    int vehicleId, capacity;
    string driverName;
    bool isAvailable;
    cout << "Enter the Vehicle Id : ";
    cin >> vehicleId;
    cout << "Enter the Capacity : ";
    cin >> capacity;
    cout << "Enter the driverName : ";
    cin >> driverName;
    cout << "Is the Car Available for Delivery : ";
    cin >> isAvailable;
    Vehicle newVehicle(vehicleId, driverName, capacity, isAvailable);
    for (auto it = m_vehicles->begin(); it != m_vehicles->end(); ++it)
    {
        if (it->getVehicleId() == vehicleId)
        {
            cout << "Error: Vehicle '" << vehicleId << "' already exists.\n";
            return;
        }
    }
    m_vehicles->push_back(newVehicle);
    cout << "Vehicle '" << vehicleId << "' added successfully.\n";
}
void WarehouseController::addProduct()
{
    int productId, qualityScore, stockQuantity;
    string productName;
    cout << "Enter the Product Id : ";
    cin >> productId;
    cout << "Enter the Product Name : ";
    cin >> productName;
    cout << "Enter the Stock quantity : ";
    cin >> stockQuantity;
    cout << "Enter the Quality score : ";
    cin >> qualityScore;
    for (auto it = m_products->begin(); it != m_products->end(); ++it)
    {
        if (it->getProductId() == productId)
        {
            it->updateStock(stockQuantity);
            cout << "Product '" << productId << "' already exists. Stock updated.\n";
            return;
        }
    }
    Product newProduct(productId, productName, stockQuantity, qualityScore);
    m_products->push_back(newProduct);
    cout << "Product '" << productName << "' added successfully.\n";
}
void WarehouseController::addStore()
{
    int storeId;
    string storeName, location;
    cout << "Enter the store ID : ";
    cin >> storeId;
    cout << "Enter the Store Name : ";
    cin >> storeName;
    cout << "Enter the Store Location : ";
    cin >> location;
    Store newStore(storeId, storeName, location);
    for (auto it = m_stores->begin(); it != m_stores->end(); ++it)
    {
        if (it->getStoreId() == storeId)
        {
            cout << "Error: Store '" << storeId << "' already exists.\n";
            return;
        }
    }
    m_stores->push_back(newStore);
    cout << "Store '" << storeName << "' added successfully.\n";
}
void WarehouseController::listVehicles() const
{
    if (m_vehicles->empty())
    {
        cout << "No vehicles available.\n";
        return;
    }
    cout << "--- Vehicle List ---\n";
    for (auto it = m_vehicles->begin(); it != m_vehicles->end(); ++it)
    {
        cout << "Vehicle ID: " << it->getVehicleId()
            << "| Driver: " << it->getdriverName()
            << "| Capacity: " << it->getcapacity()
            << "| Available: " << (it->getIsAvailable() ? "Yes" : "No") << "\n";
    }
}
void WarehouseController::dispatchProduct()
{
    int productId, storeId, quantity;
    if (m_products->empty()) {
        cout << "No product available to assign.\n";
        return;
    }
    listProducts();
    cout << "Enter the Product Id: ";
    cin >> productId;
    if (m_stores->empty()) {
        cout << "No stores available to assign.\n";
        return;
    }
    listStores();
    cout << "Enter the Store Id: ";
    cin >> storeId;
    cout << "Enter the Quantity: ";
    cin >> quantity;
    shared_ptr<Product> selectedProduct = nullptr;
    for (auto it = m_products->begin(); it != m_products->end(); ++it) {
        if (it->getProductId() == productId) {
            if (it->getStockQuantity() < quantity) {
                cout << "Error: Not enough stock for Product '" << productId << "'.\n";
                return;
            }
            it->updateStock(-quantity);
            selectedProduct = make_shared<Product>(*it); // wrap object in shared_ptr
            break;
        }
    }
    if (!selectedProduct) {
        cout << "Error: Product '" << productId << "' not found.\n";
        return;
    }
    shared_ptr<Store> selectedStore = nullptr;
    for (auto st = m_stores->begin(); st != m_stores->end(); ++st) {
        if (st->getStoreId() == storeId) {
            selectedStore = make_shared<Store>(*st); // wrap object in shared_ptr
            break;
        }
    }
    if (!selectedStore) {
        cout << "Error: Store '" << storeId << "' not found.\n";
        return;
    }
    DeliveryItem item(quantity, selectedProduct, selectedStore);
    m_dispatchPendingProduct->push_back(item);
    cout << "Product '" << productId << "' queued for quality check before dispatch to Store '" << storeId << "'.\n";
}
void WarehouseController::listProducts() const
{
    if (m_products->empty())
    {
        cout << "No products available in the warehouse.\n";
        return;
    }
    cout << "\n--- Product List ---\n";
    for (auto it = m_products->begin(); it != m_products->end(); ++it)
    {
        cout << "Product ID: " << it->getProductId()
            << "| Name: " << it->getProductName()
            << "| Stock: " << it->getStockQuantity()
            << "| Quality Score: " << it->getQualityScore()
            << "| Status: " << it->getStatus() << "\n";
    }
}
void WarehouseController::listStores() const
{
    if (m_stores->empty())
    {
        cout << "No stores registered.\n";
        return;
    }
    cout << "--- Store List ---\n";
    for (auto it = m_stores->begin(); it != m_stores->end(); ++it)
    {
        cout << "Store ID: " << it->getStoreId()
            << "| Name: " << it->getStoreName()
            << "| Location: " << it->getStoreLocation() << "\n";
    }
}
void WarehouseController::updateDeliveryStatus()
{
    int deliveryId;
    cout << "Enter Delivery ID to update: ";
    cin >> deliveryId;
    for (auto it = m_deliveries->begin(); it != m_deliveries->end(); ++it)
    {
        if (it->getDeliveryId() == deliveryId)
        {
            string currentStatus = it->getDeliveryStatus();
            cout << "Current status: " << currentStatus << "\n";
            int choice;
            cout << "Select new status:\n";
            cout << "1. Dispatched\n";
            cout << "2. In Transit\n";
            cout << "3. Delivered\n";
            cin >> choice;
            if (currentStatus == "Delivered") {
                cout << "Error: Delivery is already completed and cannot be changed.\n";
                return;
            }
            if (currentStatus == "In Transit" && choice == 1) {
                cout << "Error: Cannot change status from In Transit back to Dispatched.\n";
                return;
            }
            switch (choice)
            {
            case 1: it->updateDeliveryStatus("Dispatched");
                break;
            case 2: it->updateDeliveryStatus("In Transit"); 
                break;
            case 3: it->updateDeliveryStatus("Delivered");
                break;
            default: cout << "Invalid status choice.\n";
                return;
            }
            cout << "Delivery " << deliveryId << " status updated successfully.\n";
            return;
        }
    }
    cout << "Error: Delivery with ID " << deliveryId << " not found.\n";
}
void WarehouseController::listDispatchPendingItems()
{
    if (m_dispatchPendingProduct->empty())
    {
        cout << "No items pending to dispatch.\n";
        return;
    }
    cout << "--- Dispatch Pending Items ---\n";
    for (auto it = m_dispatchPendingProduct->begin(); it != m_dispatchPendingProduct->end(); ++it)
    {
        Product& product = *(it->getProduct());
        cout << "Product ID: " << product.getProductId()
            << "| Name: " << product.getProductName()
            << "| Quantity: " << it->getQuantity()
            << "| Status: " << product.getStatus() << "\n";
    }
}
void WarehouseController::listDeliveries() const
{
    if (m_deliveries->empty()) {
        std::cout << "No deliveries available.\n";
        return;
    }
    for (auto it = m_deliveries->begin(); it != m_deliveries->end(); ++it) {
        std::cout << "Delivery ID: " << it->getDeliveryId()
            << " | Status: " << it->getDeliveryStatus()
            << " | Address: " << it->getDeliveryAddress() << "\n";
        std::shared_ptr<Store> store = it->getStore();
        if (store) {
            std::cout << "  Store ID: " << store->getStoreId()
                << " | Location: " << store->getStoreLocation() << "\n";
        }
        std::shared_ptr<Vehicle> vehicle = it->getVehicle();
        if (vehicle) {
            std::cout << "  Vehicle ID: " << vehicle->getVehicleId()
                << " | Driver Name: " << vehicle->getdriverName()
                << " | Available: " << (vehicle->getIsAvailable() ? "Yes" : "No") << "\n";
        }
        std::cout << "  Items:\n";
        for (auto itemIt = it->getItems().begin(); itemIt != it->getItems().end(); ++itemIt) {
            std::shared_ptr<Product> product = itemIt->getProduct();
            if (product) {
                std::cout << "    Product ID: " << product->getProductId()
                    << " | Name: " << product->getProductName()
                    << " | Quantity: " << itemIt->getQuantity() << "\n";
            }
        }
        std::cout << "-----------------------------------\n";
    }
}
void WarehouseController::performQualityCheck()
{
    if (m_dispatchPendingProduct->empty())
    {
        cout << "No items pending quality check.\n";
        return;
    }
    for (auto it = m_dispatchPendingProduct->begin(); it != m_dispatchPendingProduct->end(); )
    {
        Product& product = *(it->getProduct());
        if (product.getQualityScore() >= m_qualityCheck.getThreshold())
        {
            product.updateStatus("Approved");
            ++it;
        }
        else
        {
            product.updateStatus("Damaged");
            m_damagedProducts->push_back(*it);
            it = m_dispatchPendingProduct->erase(it);
        }
    }
}
void WarehouseController::removeUser()
{
    int userId;
    cout << "Enter User ID to remove: ";
    cin >> userId;

    for (auto it = m_users->begin(); it != m_users->end(); ++it)
    {
        if (it->getUserId() == userId)
        {
            /*m_users->erase(it);*/
            it->updateUserStatus("Removed");
            cout << "User with ID " << userId << " removed successfully.\n";
            return;
        }
    }
    cout << "Error: User with ID " << userId << " not found.\n";
}
void WarehouseController::removeProduct()
{
    int productId;
    cout << "Enter Product ID to remove: ";
    cin >> productId;

    for (auto it = m_products->begin(); it != m_products->end(); ++it)
    {
        if (it->getProductId() == productId)
        {
            m_products->erase(it);
            cout << "Product with ID " << productId << " removed successfully.\n";
            return;
        }
    }
    cout << "Error: Product with ID " << productId << " not found.\n";
}
void WarehouseController::removeVehicle()
{
    int vehicleId;
    cout << "Enter Vehicle ID to remove: ";
    cin >> vehicleId;

    for (auto it = m_vehicles->begin(); it != m_vehicles->end(); ++it)
    {
        if (it->getVehicleId() == vehicleId)
        {
            m_vehicles->erase(it);
            cout << "Vehicle with ID " << vehicleId << " removed successfully.\n";
            return;
        }
    }
    cout << "Error: Vehicle with ID " << vehicleId << " not found.\n";
}
void WarehouseController::removeStore()
{
    int storeId;
    cout << "Enter Store ID to remove: ";
    cin >> storeId;

    for (auto it = m_stores->begin(); it != m_stores->end(); ++it)
    {
        if (it->getStoreId() == storeId)
        {
            m_stores->erase(it);
            cout << "Store with ID " << storeId << " removed successfully.\n";
            return;
        }
    }
    cout << "Error: Store with ID " << storeId << " not found.\n";
}
void WarehouseController::acceptDelivery()
{
    if (m_dispatchPendingProduct->empty()) {
        std::cout << "No items pending delivery.\n";
        return;
    }
    int deliveryId = static_cast<int>(m_deliveries->size()) + 1;
    std::shared_ptr<Store> store = m_dispatchPendingProduct->front().getStore();
    Delivery newDelivery(deliveryId, store->getStoreLocation(), store);
    for (auto it = m_dispatchPendingProduct->begin(); it != m_dispatchPendingProduct->end(); ++it) {
        newDelivery.getItems().push_back(*it);
    }
    listVehicles();
    int vehicleId;
    std::cout << "Enter Vehicle ID to assign: ";
    std::cin >> vehicleId;
    std::shared_ptr<Vehicle> selectedVehicle = nullptr;
    for (auto it = m_vehicles->begin(); it != m_vehicles->end(); ++it) {
        if (it->getVehicleId() == vehicleId && it->getIsAvailable()) {
            it->setIsAvailable(false);
            selectedVehicle = std::make_shared<Vehicle>(*it);
            break;
        }
    }
    if (!selectedVehicle) {
        std::cout << "Error: Vehicle '" << vehicleId << "' not found or not available.\n";
        return;
    }
    newDelivery.assignVehicle(selectedVehicle);
    newDelivery.updateDeliveryStatus("In Transit");
    m_deliveries->push_back(newDelivery);
    m_dispatchPendingProduct->clear();
    std::cout << "Delivery " << deliveryId << " accepted and set In Transit.\n";
}
shared_ptr<vector<Product>> WarehouseController::getProducts()
{
    return m_products;
}
shared_ptr<vector<User>> WarehouseController::getUsers()
{
    return m_users;
}
shared_ptr<vector<Vehicle>> WarehouseController::getVehicles()
{
    return m_vehicles;
}
shared_ptr<vector<Store>> WarehouseController::getStores()
{
    return m_stores;
}

