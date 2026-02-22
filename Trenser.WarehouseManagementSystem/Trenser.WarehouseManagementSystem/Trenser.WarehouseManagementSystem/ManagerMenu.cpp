#include "WarehouseController.h"
#include "ManagerMenu.h"
using namespace std;

void ManagerMenu::showMenu()
{
    cout << "\n=== Manager Menu ===\n";
    cout << "1. Add Product\n";
    cout << "2. Remove Product\n";
    cout << "3. Add Vehicle\n";
    cout << "4. Remove Vehicle\n";
    cout << "5. Add Store\n";
    cout << "6. Remove Store\n";
    cout << "7. Dispatch Delivery\n";
    cout << "8. List Products\n";
    cout << "9. List Stores\n";
    cout << "10. List Vehicles\n";
    cout << "11. List Dispatch Pending\n";
    cout << "12. List Deliveries\n";
    cout << "13. Logout\n";
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
        case 1: controller.addProduct(); break;
        case 2: controller.removeProduct(); break;
        case 3: controller.addVehicle(); break;
        case 4: controller.removeVehicle(); break;
        case 5: controller.addStore(); break;
        case 6: controller.removeStore(); break;
        case 7: controller.dispatchProduct(); break;
        case 8: controller.listProducts(); break;
        case 9: controller.listStores(); break;
        case 10: controller.listVehicles(); break;
        case 11: controller.listDispatchPendingItems(); break;
        case 12: controller.listDeliveries(); break;
        case 13: cout << "Logging out...\n"; break;
        default: cout << "Invalid choice.\n"; break;
        }

    } while (choice != 13);
}