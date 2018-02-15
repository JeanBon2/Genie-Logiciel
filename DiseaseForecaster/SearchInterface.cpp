// System include
#include <iostream>
#include <string>
using namespace std;
// Personnal include
#include "SearchInterface.h"

// Constants

// Constructors
SearchInterface::SearchInterface()
{
#ifdef DEBUG
	cout << "SearchInterface constructor call" << endl;
#endif // DEBUG
	stage = SEARCHING;
	getInterfaceText();
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
	case SEARCHING:
		interfaceText = getText("SearchInterface_Search");
		stage = DISPLAYING;
		break;
	case DISPLAYING:
		interfaceText += getText("SearchInterface_ResultList")+"\n";
		interfaceText += getText("SearchInterface_SearchNumber");
		stage = INTERACTING;
		break;
	case INTERACTING:
		interfaceText += getText("SearchInterface_Delete");
		interfaceText += getText("Interface_Previous") + "\n";
		stage = SEARCHING;
		break;
	default:
		interfaceText += getText("Unknown_Command") + "\n";
		break;
	}
	cout << interfaceText << endl;
}
string SearchInterface::getAction()
{
	return "";
}
void SearchInterface::searchHealthPrint(string patientName)
{}
bool SearchInterface::remove(unsigned int printNumber)
{
	return true;
}


// Private methods
