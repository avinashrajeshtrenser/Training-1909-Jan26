#include "WarehouseController.h"
#include "StaffMenu.h"
using namespace std;
void StaffMenu::showMenu()
{
    cout << "\n=== Staff Menu ===\n";
    cout << "1. Perform Quality Check\n";
    cout << "2. Update Delivery Status\n";
    cout << "3. Accept Delivery Task\n";
    cout << "4. Logout\n";
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
        case 1: controller.performQualityCheck();
            break;
        case 2: controller.updateDeliveryStatus();
            break;
        case 3: controller.acceptDelivery();
            break;
        case 4: controller.listProducts();
            break;
        case 5: controller.listStores();
            break;
        case 6: controller.listVehicles();
            break;
        case 7: controller.listDispatchPendingItems();
            break;
        case 8: controller.listDeliveries();
            break;
        case 9: cout << "Logging out...\n";
            break;
        default: cout << "Invalid choice.\n";
            break;
        }
    } while (choice != 9);
}
