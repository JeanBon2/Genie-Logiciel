// System include
using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

// Personnal include
#include "MenuInterface.h"

// Constants

// Constructors
MenuInterface::MenuInterface()
{
#ifdef DEBUG
	cout << "Xxx constructor call" << endl;
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
	string updateDate = "";
	menuContent += Interface::getText("LastUpdate")+":"+updateDate+"\n";
	menuContent += Interface::getText("ProductName")+" Version "+ Interface::getText("Version")+"\n";
	menuContent += '\n';
	menuContent += "1: "+ Interface::getText("MenuInterface_AnalysePrint")+"\n";
	menuContent += "2: " + Interface::getText("MenuInterface_Synchronisation") + "\n";
	menuContent += "3: " + Interface::getText("MenuInterface_Search") + "\n";
	menuContent += "\n";
	menuContent += "4: " + Interface::getText("MenuInterface_Log") + "\n";
	menuContent += "5: " + Interface::getText("MenuInterface_Leave") + "\n";
	menuContent += "6: " + Interface::getText("MenuInterface_Help") + "\n";
	menuContent += "\n";
	menuContent += Interface::getText("MenuInterface_GetAction") + "\n";

	cout<<menuContent;
}

const string MenuInterface::getAction()
{
	
	
	string choiceMenu = 0;
	while(choiceMenu != 5)
	{
		int interfaceId;
		cin >> choiceMenu;

		switch (stoi(choiceMenu))
		{
		case 1:
			Interface::createInterface(4);
			break;
		case 2:
			Interface::createInterface(3);
			break;
		case 3:
			Interface::createInterface(2);
			break;
		case 4:
			//LOG
			break;

		case 5:
			//QUIT
			break;
		case 6:
			//HELP
			string command = "iexplore";
			GetCurrentDirectoryA(sizeof(working_directory), working_directory); // **** win32 specific ****
			command.append(working_directory)
				break;
		default:
			break;
		}
	}

	return choiceMenu;

}
