#pragma once
class Menu
{
public:
	Menu() {}
	virtual void Menu()=0;
	virtual void handleOperation(int choice)=0;
};

	