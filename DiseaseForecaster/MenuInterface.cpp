//menu
// System include
using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#define DEBUG
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
	getAction();
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
	menuContent += "1: " + getText("MenuInterface_AnalysePrint") + "\n";
	menuContent += "2: " + getText("MenuInterface_Synchronisation") + "\n";
	menuContent += "3: " + getText("MenuInterface_Search") + "\n";
	menuContent += "\n";
	menuContent += "4: " + getText("MenuInterface_Log") + "\n";
	menuContent += "5: " + getText("MenuInterface_Leave") + "\n";
	menuContent += "6: " + getText("MenuInterface_Help") + "\n";
	menuContent += "\n";
	menuContent += getText("MenuInterface_GetAction") + "\n";

	cout << menuContent;
}

string MenuInterface::getAction()
{
	string returnValue="";
	string choiceMenu = "0";
	int actionToDo;

	while (choiceMenu != "5")
	{
		getInterfaceText();
		getline(cin, choiceMenu);
		try
		{
			actionToDo = stoi(choiceMenu);
		}
		catch(invalid_argument& i)
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
			case 4:
				//LOG
				break;

			case 5:
				cout << getText("Leave_App");
				break;
			case 6:
				//HELP

			//string command = "iexplore";
			//GetCurrentDirectoryA(sizeof(working_directory), working_directory); // **** win32 specific ****
			//command.append(working_directory)

			break;
		default:
			system("cls");
			cout << getText("Unknown_Command") << endl;
			break;
		}
	}
	returnValue += choiceMenu;

	return returnValue;

}
