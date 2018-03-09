//menu
// System include
using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

// Personnal include
#include "MenuInterface.h"
#include "Log.h"

// Constants

// Constructors
MenuInterface::MenuInterface()
{
#ifdef DEBUG
	cout << "MenuInterface constructor call" << endl;
#endif // DEBUG
}

MenuInterface::MenuInterface(const MenuInterface*)
{
#ifdef DEBUG
	cout << "Xxx copy constructor call" << endl;
#endif // DEBUG

}

// Destructor
MenuInterface::~MenuInterface()
{
#ifdef DEBUG
	cout << "Xxx destructor call" << endl;
#endif // DEBUG
}

// Public methods

// Protected methods
void MenuInterface::displayInterfaceText()
{
	string menuContent = "";
	string lastUpdateDate = "";
	menuContent += getTextFromField("LastUpdate") + lastUpdateDate + "\n";
	menuContent += getTextFromField("ProductName") + " Version " + getTextFromField("Version") + "\n";
	menuContent += '\n';
	menuContent += to_string(UPDATE_INTERFACE) + " : " + getTextFromField("MenuInterface_Update") + "\n";
	menuContent += to_string(EXPORT_INTERFACE) + " : " + getTextFromField("MenuInterface_Export") + "\n";
	menuContent += "\n";
	menuContent += to_string(LEAVE_INTERFACE) + " : " + getTextFromField("MenuInterface_Leave") + "\n";
	menuContent += "\n";
	menuContent += getTextFromField("MenuInterface_GetAction") + "\n";

	cout << menuContent;
}


void MenuInterface::run()
{
	string choiceMenu="";
	int actionToDo;
	bool leave = false;
	

	while (!leave)
	{
		system("cls");
		displayInterfaceText();
		choiceMenu = getAction();
		try
		{
			actionToDo = stoi(choiceMenu);
		}
		catch (invalid_argument& )
		{
			actionToDo = 0;
		}
		catch (out_of_range&)
		{
			actionToDo = 0;
		}
		switch (actionToDo)
		{
			
			case UPDATE_INTERFACE:
				//Synchro
				createInterface(UPDATE_INTERFACE);
				break;
			case EXPORT_INTERFACE:
				//Search
				createInterface(EXPORT_INTERFACE);
				break;

			case LEAVE_INTERFACE:
				createInterface(LEAVE_INTERFACE);
				leave = true;
				break;

			default:
				cout << getTextFromField("Unknown_Command") << endl;
				break;
		}
	}
}