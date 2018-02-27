// System include
#include <iostream>
#include <string>
using namespace std;
// Personnal include
#include "SearchInterface.h"
#include "Analyse.h"

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
void SearchInterface::displayInterfaceText()
{
	string interfaceText="";
	switch (stage)
	{
		case WELCOME:
			interfaceText = getTextFromField("SearchInterface_Search");
			break;
		case RESULTS:
			interfaceText = getTextFromField("SearchInterface_ResultList")+"\n";
			interfaceText += getTextFromField("SearchInterface_SearchNumber");
			break;
		case INTERACT:
			interfaceText = getTextFromField("SearchInterface_Delete");
			interfaceText += getTextFromField("Interface_Previous") + "\n";
			break;

		default:
			interfaceText = getTextFromField("Unknown_Command") + "\n";
			break;
	}
	cout << interfaceText << endl;
}

void SearchInterface::run()
{
	string inputValue;
	unsigned int analyseSelected;
	unsigned int displayerCounter = 0;

	while (stage != LEAVE)
	{
		displayInterfaceText();
		inputValue = getAction();
		
		switch (stage)
		{
		case WELCOME:
			//chercher dans la Database
			//resultsFromSearch = fontion de recherche(getAction())
			stage = RESULTS;
			break;

		case RESULTS:
			//afficher les résultats de la database
				
			for (Analyse& analyse : resultsFromRequest)
			{
				cout << ++displayerCounter << " : ";
				analyse.displayHeader();
			}
			stage = INTERACT;
			break;

		case INTERACT:
			if (inputValue == "0")
			{
				stage = LEAVE;
				break;
			}
			else if (inputValue == "1")
			{
				try
				{
					analyseSelected = stoi(inputValue);
					if (analyseSelected >= resultsFromRequest.size())
					{
						analyseSelected = 0;
					}
				}
				catch (invalid_argument& i)
				{
					analyseSelected = 0;
				}
				catch (out_of_range& o)
				{
					analyseSelected = 0;
				}
				if (analyseSelected != 0)
				{
					resultsFromRequest[analyseSelected - 1].displayContent();
				}
				else
				{
					stage = WELCOME;
				}
				remove(analyseSelected - 1);
				stage = WELCOME;
			}
			
			break;

		default:
			stage = LEAVE;
			break;
		}
	}
	
}
void SearchInterface::searchAnalyse(string patientName)
{}
bool SearchInterface::remove(unsigned int printNumber)
{
	//TO DO
	//CODE POUR SUPPRIMER DE LA DB
	cout << getTextFromField("Search_Interface_ConfirmDelete") << endl;
	return true;
}


// Private methods
