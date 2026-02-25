#include "WarehouseController.h"
#include "AdminMenu.h"
using namespace std;

void AdminMenu::showMenu()
{
    cout << "\n=== Admin Menu ===\n";
    cout << "1. Add User (Manager/Staff)\n";
    cout << "2. Remove User\n";
    cout << "3. Add Product\n";
    cout << "4. Remove Product\n";
    cout << "5. Add Vehicle\n";
    cout << "6. Remove Vehicle\n";
    cout << "7. Add Store\n";
    cout << "8. Remove Store\n";
    cout << "9. Dispatch Delivery\n";
    cout << "10. Accept Delivery\n";
    cout << "11. Perform Quality Check\n";
    cout << "12. List Products\n";
    cout << "13. List Stores\n";
    cout << "14. List Vehicles\n";
    cout << "15. List Pending Dispatch\n";
    cout << "16. List Deliveries\n";
    cout << "17. Update Delivery Status\n";
    cout << "18. Logout\n";
}
void AdminMenu::handleOperation(WarehouseController& controller)
{
    int choice;
    do {
        showMenu();
        cout << "\nEnter The choice : ";
        cin >> choice;
        cout << endl;
        switch (choice) {
        case 1: controller.addUser(); break;
        case 2: controller.removeUser(); break;
        case 3: controller.addProduct(); break;
        case 4: controller.removeProduct(); break;
        case 5: controller.addVehicle(); break;
        case 6: controller.removeVehicle(); break;
        case 7: controller.addStore(); break;
        case 8: controller.removeStore(); break;
        case 9: controller.addToDispatchQueue(); break;
        case 10: controller.dispatchDelivery(); break;
        case 11: controller.performQualityCheck(); break;
        case 12: controller.listProducts(); break;
        case 13: controller.listStores(); break;
        case 14: controller.listVehicles(); break;
        case 15: controller.listDispatchPendingItems(); break;
        case 16: controller.listDeliveries(); break;
        case 17: controller.updateDeliveryStatus(); break;
        case 18: cout << "Logging out\n"; break;
        default: cout << "Invalid choice.\n"; break;
        }
    } while (choice != 18);
}
