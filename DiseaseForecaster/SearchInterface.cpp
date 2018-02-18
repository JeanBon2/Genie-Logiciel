// System include
#include <iostream>
#include <string>
using namespace std;
// Personnal include
#include "SearchInterface.h"

// Constants

// Constructors
SearchInterface::SearchInterface():stage(WELCOME)
{
#ifdef DEBUG
	cout << "SearchInterface constructor call" << endl;
#endif // DEBUG
}

// Destructor
SearchInterface::~SearchInterface()
{
#ifdef DEBUG
	cout << "SearchInterface destructor call" << endl;
#endif // DEBUG
}

// Public methods


// Protected methods
void SearchInterface::getInterfaceText()
{
	string interfaceText="";
	switch (stage)
	{
		case WELCOME:
			interfaceText = getText("SearchInterface_Search");
			break;
		case RESULTS:
			interfaceText = getText("SearchInterface_ResultList")+"\n";
			interfaceText += getText("SearchInterface_SearchNumber");
			break;
		case INTERACT:
			interfaceText = getText("SearchInterface_Delete");
			interfaceText += getText("Interface_Previous") + "\n";
			break;

		default:
			interfaceText = getText("Unknown_Command") + "\n";
			break;
	}
	cout << interfaceText << endl;
}

void SearchInterface::run()
{
	string inputValue;
	while (true)
	{
		getInterfaceText();
		inputValue = getAction();
		while (stage != LEAVE)
		{
			switch (stage)
			{
			case WELCOME:
				//chercher dans la Database
				stage = RESULTS;
				break;

			case RESULTS:
				//afficher les résultats de la database
				stage = INTERACT;
				break;

			case INTERACT:
				//supprimer ou revenir à la recherche
				if (inputValue == "1")
				{
					stage = WELCOME;
				}
				else if (inputValue == "0")
				{
					stage = LEAVE;
				}
				break;

			default:
				stage = LEAVE;
				break;
			}
		}
		
	}
	
}
void SearchInterface::searchHealthPrint(string patientName)
{}
bool SearchInterface::remove(unsigned int printNumber)
{
	return true;
}


// Private methods
