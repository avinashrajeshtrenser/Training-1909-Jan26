#pragma once
#include <iostream>
#include "Menu.h"
class AdminMenu : public Menu
{
public:
	void showMenu() override;
	void handleOperation(int choice) override;
};

