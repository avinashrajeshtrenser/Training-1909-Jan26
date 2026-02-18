#pragma once
#include <iostream>
#include "Menu.h"
class ManagerMenu : public Menu
{
public:
	void showMenu() override;
	void handleOperation() override;
};

