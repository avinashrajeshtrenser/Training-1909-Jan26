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
		std::string username, password, role;
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

bool WarehouseController::authorizeUser(const std::string& username, const std::string& password)
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
	std::string username, password, role;
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
	std::string username, password, role;
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
			std::cout << "Error: Username '" << username << "' already exists.\n";
			return;
		}
	}
	m_users.push_back(newUser);
	std::cout << "User '" << username << "' registered successfully.\n";
}

void WarehouseController::addVehicle()
{
	int vehicleId, capacity;
	std::string driverName;
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
			std::cout << "Error: Vehicle '" << vehicleId << "' already exists.\n";
			return;
		}
	}
	m_vehicles.push_back(newVehicle);
	std::cout << "Vehicle '" << vehicleId << "' added successfully.\n";
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
			std::cout << "Error: Store '" << storeId << "' already exists.\n";
			return;
		}
	}
	m_stores.push_back(newStore);
	std::cout << "Store '" << storeId << "' added successfully.\n";
}

void WarehouseController::addProduct()
{
	int productId, qualityScore, stockQuantity;
	std::string productName;
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
			it->updateStockIncrease(stockQuantity);
			std::cout << "Product '" << productId << "' already exists. Stock updated.\n";
			return;
		}
	}
	Product newProduct(productId, productName, stockQuantity, qualityScore);
	m_products.push_back(newProduct);
	std::cout << "Vehicle '" << productId << "' added successfully.\n";
}
