#include <iostream>
#include "WarehouseController.h"
using namespace std;
int main()
{
    try
    {
        WarehouseController* controller = new WarehouseController();
        controller->loadSystem();
        controller->controllerMenu();
    }
    catch (...)
    {
        cout << "Exception Occured.\n";
    }
}

