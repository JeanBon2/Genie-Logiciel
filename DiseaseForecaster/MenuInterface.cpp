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

MenuInterface::MenuInterface(const MenuInterface* x)
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
void MenuInterface::getInterfaceText()
{
	string menuContent = "";
	string lastUpdateDate = "";
	menuContent += getText("LastUpdate") + lastUpdateDate + "\n";
	menuContent += getText("ProductName") + " Version " + getText("Version") + "\n";
	menuContent += '\n';
	menuContent += to_string(ANALYSE_INTERFACE) + " : " + getText("MenuInterface_AnalysePrint") + "\n";
	menuContent += to_string(UPDATE_INTERFACE) + " : " + getText("MenuInterface_Synchronisation") + "\n";
	menuContent += to_string(SEARCH_INTERFACE) + " : " + getText("MenuInterface_Search") + "\n";
	menuContent += "\n";
	menuContent += to_string(LOG_INTERFACE) + " : " + getText("MenuInterface_Log") + "\n";
	menuContent += to_string(LEAVE_INTERFACE) + " : " + getText("MenuInterface_Leave") + "\n";
	menuContent += to_string(HELP_INTERFACE) + " : " + getText("MenuInterface_Help") + "\n";
	menuContent += "\n";
	menuContent += getText("MenuInterface_GetAction") + "\n";

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
		getInterfaceText();
		choiceMenu = getAction();
		try
		{
			actionToDo = stoi(choiceMenu);
		}
		catch (invalid_argument& i)
		{
			actionToDo = 0;
		}
		catch (out_of_range& o)
		{
			actionToDo = 0;
		}
		switch (actionToDo)
		{
			case ANALYSE_INTERFACE:
				//Analyse
				createInterface(ANALYSE_INTERFACE);
				break;
			case UPDATE_INTERFACE:
				//Synchro
				createInterface(UPDATE_INTERFACE);
				break;
			case SEARCH_INTERFACE:
				//Search
				createInterface(SEARCH_INTERFACE);
				break;
			case LOG_INTERFACE:
				createInterface(LOG_INTERFACE);
				break;

			case LEAVE_INTERFACE:
				createInterface(LEAVE_INTERFACE);
				leave = true;
				break;

			case HELP_INTERFACE:
				createInterface(HELP_INTERFACE);
				break;

			default:
				cout << getText("Unknown_Command") << endl;
				break;
		}
	}
}