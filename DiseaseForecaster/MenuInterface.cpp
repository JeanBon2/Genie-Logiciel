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

// Protected methods
void MenuInterface::displayInterfaceText()
{
	string menuContent = "";
	string lastUpdateDate = "";
	menuContent += getTextFromField("LastUpdate") + lastUpdateDate + "\n";
	menuContent += getTextFromField("ProductName") + " Version " + getTextFromField("Version") + "\n";
	menuContent += '\n';
	menuContent += to_string(ANALYSE_INTERFACE) + " : " + getTextFromField("MenuInterface_AnalysePrint") + "\n";
	menuContent += to_string(UPDATE_INTERFACE) + " : " + getTextFromField("MenuInterface_Synchronisation") + "\n";
	menuContent += to_string(SEARCH_INTERFACE) + " : " + getTextFromField("MenuInterface_Search") + "\n";
	menuContent += "\n";
	menuContent += to_string(LOG_INTERFACE) + " : " + getTextFromField("MenuInterface_Log") + "\n";
	menuContent += to_string(LEAVE_INTERFACE) + " : " + getTextFromField("MenuInterface_Leave") + "\n";
	menuContent += to_string(HELP_INTERFACE) + " : " + getTextFromField("MenuInterface_Help") + "\n";
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
				cout << getTextFromField("Unknown_Command") << endl;
				break;
		}
	}
}
