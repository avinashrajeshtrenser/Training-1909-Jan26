#include "WarehouseController.h"
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
        case 1: controller.addProduct();
            break;
        case 2: controller.addVehicle();
            break;
        case 3: controller.addStore();
            break;
        case 4: controller.dispatchProduct();
            break;
        case 5: controller.listProducts();
            break;
        case 6: controller.listStores();
            break;
        case 7: controller.listVehicles();
            break;
        case 8: controller.listDispatchPendingItems();
            break;
        case 9: /*controller.listDeliveries();*/
            break;
        case 10: cout << "Logging out...\n";
            break;
        default: cout << "Invalid choice.\n";
            break;
        }
    } while (choice != 10);
}
