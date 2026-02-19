#pragma once
#include <iostream>
#include "Menu.h"
class StaffMenu : public Menu
{
public:
	void showMenu() override;
	void handleOperation(WarehouseController&) override;
};

