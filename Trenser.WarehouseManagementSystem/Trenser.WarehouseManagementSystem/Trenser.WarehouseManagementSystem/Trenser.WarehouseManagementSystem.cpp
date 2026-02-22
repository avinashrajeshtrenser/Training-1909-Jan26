#include <iostream>
#include "WarehouseController.h"
using namespace std;
int main()
{
    WarehouseController* controller = new WarehouseController();
    controller->loadSystem();
    controller->controllerMenu();
}

