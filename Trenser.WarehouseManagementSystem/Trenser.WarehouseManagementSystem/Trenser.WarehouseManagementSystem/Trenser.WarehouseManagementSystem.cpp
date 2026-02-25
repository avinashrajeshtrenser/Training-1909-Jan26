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
        delete controller;
    }
    catch (const exception& e)
    {
        cout << "Exception Occured.\n";
    }
}

