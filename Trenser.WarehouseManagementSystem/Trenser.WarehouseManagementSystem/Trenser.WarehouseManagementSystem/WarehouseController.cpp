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
		if (choice == 1)
		{
			/*cout << "Enter the Username : ";
			cin >> username;
			cout << "Enter Password : ";
			cin >> password;
			cout << "Enter the role (Admin, Manager, Staff): ";
			cin >> role;
			User newUser(m_users.size() + 1, username, password, role);	
			addUser(newUser);*/
			addUser();
		}
		if (choice == 2)
		{
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
					m_menu->handleOperation();
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


void WarehouseController::addUser()
{
	std::string username, password, role;
	cout << "Enter the Username : ";
	cin >> username;
	cout << "Enter Password : ";
	cin >> password;
	cout << "Enter the role (Admin, Manager, Staff): ";
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
//void WarehouseController::addUser(User& user)
//{
//	for (auto it = m_users.begin(); it != m_users.end(); ++it)
//	{
//		if (it->getUserName() == user.getUserName())
//		{
//			std::cout << "Error: Username '" << user.getUserName() << "' already exists.\n";
//			return;
//		}
//	}
//	m_users.push_back(user);
//	std::cout << "User '" << user.getUserName() << "' registered successfully.\n";
//}

