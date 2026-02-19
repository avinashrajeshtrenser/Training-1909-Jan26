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
		/*if (choice == 1)
		{
			addUser();
		}
		if (choice == 2)
		{
			loginUser();
		}*/
		switch (choice)
		{
		case 1: addUser();
			break;
		case 2: loginUser();
			break;
		case 3: exit(0);
		default: "Invalid Input. Try again";
		}
	} while (choice != 3);
}

bool WarehouseController::authorizeUser(const string& username, const string& password)
{
	for (auto it = m_users.begin(); it != m_users.end(); ++it)
	{
		if (it->getUserName() == username && it->getPassword() == password)
		{
			m_autherizedUser = *it;
			return true;
		}
	}
	return false;
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

void WarehouseController::addUser()
{
	string username, password, role;
	cout << "Enter the Username : ";
	cin >> username;
	cout << "Enter Password : ";
	cin >> password;
	cout << "Enter the role (Manager, Staff): ";
	cin >> role;
	User newUser(m_users.size() + 1, username, password, role);
	for (auto it = m_users.begin(); it != m_users.end(); ++it)
	{
		if (it->getUserName() == username)
		{
			cout << "Error: Username '" << username << "' already exists.\n";
			return;
		}
	}
	m_users.push_back(newUser);
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
	for (auto it = m_vehicles.begin(); it != m_vehicles.end(); ++it)
	{
		if (it->getVehicleId() == vehicleId)
		{
			cout << "Error: Vehicle '" << vehicleId << "' already exists.\n";
			return;
		}
	}
	m_vehicles.push_back(newVehicle);
	cout << "Vehicle '" << vehicleId << "' added successfully.\n";
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
	for (auto it = m_stores.begin(); it != m_stores.end(); ++it)
	{
		if (it->getStoreId() == storeId)
		{
			cout << "Error: Store '" << storeId << "' already exists.\n";
			return;
		}
	}
	m_stores.push_back(newStore);
	cout << "Store '" << storeId << "' added successfully.\n";
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
	for (auto it = m_products.begin(); it != m_products.end(); ++it)
	{
		if (it->getProductId() == productId)
		{
			it->updateStock(stockQuantity);
			cout << "Product '" << productId << "' already exists. Stock updated.\n";
			return;
		}
	}
	Product newProduct(productId, productName, stockQuantity, qualityScore);
	m_products.push_back(newProduct);
	cout << "Vehicle '" << productId << "' added successfully.\n";
}
void WarehouseController::dispatchProduct()
{
	int productId, storeId, quantity;
	cout << "Enter the Product Id: ";
	cin >> productId;
	cout << "Enter the Store Id: ";
	cin >> storeId;
	cout << "Enter the Quantity: ";
	cin >> quantity;
	for (auto it = m_products.begin(); it != m_products.end(); ++it)
	{
		if (it->getProductId() == productId)
		{
			if (it->getStockQuantity() < quantity)
			{
				cout << "Error: Not enough stock for Product '" << productId << "'.\n";
				return;
			}
			it->updateStock(-quantity);
			DeliveryItem item(quantity, *it);
			m_dispatchPendingProduct.push_back(item);
			cout << "Product '" << productId << "' queued for quality check before dispatch to Store '" << storeId << "'.\n";
			return;
		}
	}
	cout << "Error: Product '" << productId << "' not found.\n";
}
void WarehouseController::performQualityCheck()
{
	if (m_dispatchPendingProduct.empty())
	{
		cout << "No items pending quality check.\n";
		return;
	}
	for (auto it = m_dispatchPendingProduct.begin(); it != m_dispatchPendingProduct.end(); )
	{
		Product product = it->getProduct();
		if (product.getQualityScore() >= m_qualityCheck.getThreshold())
		{
			product.updateStatus("Approved");
			++it;
		}
		else
		{
			product.updateStatus("Damaged");
			m_damagedProducts.push_back(*it);
			it = m_dispatchPendingProduct.erase(it);
		}
	}
}


