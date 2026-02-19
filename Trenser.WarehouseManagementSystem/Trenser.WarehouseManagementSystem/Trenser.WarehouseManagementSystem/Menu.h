#pragma once
class WarehouseController;
class Menu
{
public:
	Menu() {}
	virtual void showMenu()=0;
	virtual void handleOperation(WarehouseController& )=0;
};

	