#pragma once
class Menu
{
public:
	Menu() {}
	virtual void showMenu()=0;
	virtual void handleOperation()=0;
};

	