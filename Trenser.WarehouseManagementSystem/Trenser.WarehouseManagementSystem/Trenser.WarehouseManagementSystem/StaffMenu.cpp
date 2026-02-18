#include "StaffMenu.h"
using namespace std;
void StaffMenu::showMenu()
{
    cout << "\n=== Staff Menu ===\n";
    cout << "1. Perform Quality Check\n";
    cout << "2. Update Delivery Status\n";
    cout << "3. Accept Delivery Task\n";
    cout << "4. Exit\n";
}
void StaffMenu::handleOperation()
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
        case 1: cout << "Performing quality check...\n";
            break;
        case 2: cout << "Updating delivery status...\n";
            break;
        case 3: cout << "Accepting delivery task...\n";
            break;
        case 4: cout << "Exiting Staff Menu...\n";
            break;
        default: cout << "Invalid choice.\n";
            break;
        }
    } while (choice != 4);
}
