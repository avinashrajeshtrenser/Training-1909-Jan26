#include "ManagerMenu.h"
using namespace std;

void ManagerMenu::showMenu()
{
    cout << "\n=== Manager Menu ===\n";
    cout << "1. Add Product\n";
    cout << "2. Add Vehicle\n";
    cout << "3. Add Store\n";
    cout << "4. Dispatch Delivery\n";
    cout << "5. Logout\n";
}

void ManagerMenu::handleOperation(WarehouseController& controller)
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
        case 1: cout << "Adding product...\n";
            break;
        case 2: cout << "Adding vehicle...\n";
            break;
        case 3: cout << "Adding store...\n";
            break;
        case 4: cout << "Dispatching delivery...\n";
            break;
        case 5: cout << "Logging out...\n";
            break;
        default: cout << "Invalid choice.\n";
            break;
        }
    } while (choice != 5);
}
