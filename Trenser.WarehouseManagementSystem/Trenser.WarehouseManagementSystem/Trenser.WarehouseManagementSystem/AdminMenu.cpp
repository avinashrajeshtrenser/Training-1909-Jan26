#include "WarehouseController.h"
#include "AdminMenu.h"
using namespace std;
void AdminMenu::showMenu()
{
    cout << "\n=== Admin Menu ===\n";
    cout << "1. Add User (Manager/Staff)\n";
    cout << "2. Add Product\n";
    cout << "3. Add Vehicle\n";
    cout << "4. Add Store\n";
    cout << "5. Dispatch Delivery\n";
    cout << "6. Perform Quality Check\n";
    cout << "7. Update Delivery Status\n";
    cout << "8. Logout\n";
}
void AdminMenu::handleOperation(WarehouseController& controller)
{
    int choice;
    do
    {
        showMenu();
        cout << "\nEnter The choice : ";
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1: controller.addUser(); 
            break;
        case 2: cout << "Adding product...\n";
            break;
        case 3: cout << "Adding vehicle...\n";
            break;
        case 4: cout << "Adding store...\n";
            break;
        case 5: cout << "Dispatching delivery...\n";
            break;
        case 6: cout << "Performing quality check...\n";
            break;
        case 7: cout << "Updating delivery status...\n";
            break;
        case 8: cout << "Logging out\n";
            break;
        default: cout << "Invalid choice.\n";
            break;
        }
    } while (choice != 8);
}
