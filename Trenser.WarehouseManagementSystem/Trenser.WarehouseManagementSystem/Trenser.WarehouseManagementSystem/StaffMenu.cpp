#include "WarehouseController.h"
#include "StaffMenu.h"
using namespace std;

void StaffMenu::showMenu()
{
    cout << "\n=== Staff Menu ===\n";
    cout << "1. Perform Quality Check\n";
    cout << "2. Dispatch Delivery\n";
    cout << "3. Update Delivery Status\n";
    cout << "4. List Products\n";
    cout << "5. List Stores\n";
    cout << "6. List Vehicles\n";
    cout << "7. List Dispatch Pending\n";
    cout << "8. List Deliveries\n";
    cout << "9. Logout\n";
}

void StaffMenu::handleOperation(WarehouseController& controller)
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
        case 1: controller.performQualityCheck(); break;
        case 2: controller.dispatchDelivery(); break;
        case 3: controller.updateDeliveryStatus(); break;
        case 4: controller.listProducts(); break;
        case 5: controller.listStores(); break;
        case 6: controller.listVehicles(); break;
        case 7: controller.listDispatchPendingItems(); break;
        case 8: controller.listDeliveries(); break;
        case 9: cout << "Logging out...\n"; break;
        default: cout << "Invalid choice.\n"; break;
        }
    } while (choice != 9);
}