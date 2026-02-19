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
    cout << "7. List Products\n";
    cout << "8. List Stores\n";
    cout << "9. List Vehicles\n";
    cout << "10. List Pending Dispatch\n";
    cout << "11. List Deliveries\n";
    cout << "12. Update Delivery Status\n";
    cout << "13. Logout\n";
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
        case 2: controller.addProduct();
            break;
        case 3: controller.addVehicle();
            break;
        case 4: controller.addStore();
            break;
        case 5: controller.dispatchProduct();
            break;
        case 6: controller.performQualityCheck();
            break;
        case 7: controller.listProducts();
            break;
        case 8: controller.listStores();
            break;
        case 9: controller.listVehicles();
            break;
        case 10: controller.listDispatchPendingItems();
            break;
        case 11: /*controller.listDeliveries();*/
            break;
        case 12: cout << "Updating delivery status...\n";
            break;
        case 13: cout << "Logging out\n";
            break;
        default: cout << "Invalid choice.\n";
            break;
        }
    } while (choice != 13);
}
