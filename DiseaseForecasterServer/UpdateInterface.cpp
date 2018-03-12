// System include
#include <iostream>
#include <string>
#include <QFile>
#include <qjsondocument.h>
#include <qjsonarray.h>
using namespace std;

// Personnal include
#include "UpdateInterface.h"
#include "Interface.h"
#include "ModelImporter.h"
// Constants

// Constructors
UpdateInterface::UpdateInterface()
{
}


UpdateInterface::UpdateInterface(const UpdateInterface*)
{
#ifdef DEBUG
	cout << "UpdateInterface copy constructor call" << endl;
#endif // DEBUG
}

// Destructor
UpdateInterface::~UpdateInterface()
{
#ifdef DEBUG
	cout << "UpdateInterface destructor call" << endl;
#endif // DEBUG
}

// Public methods

// Protected methods
void UpdateInterface::displayInterfaceText()
{
	switch (state)
	{
	case START_UPDATE:
		cout << getTextFromField("UpdateInterface_StartUpdate") << endl;
		break;
	case START_ANALYSIS:
		cout << getTextFromField("UpdateInterface_StartAnalysis") << endl;
		break;
	case END_ANALYSIS:
		cout << getTextFromField("UpdateInterface_EndAnalysis") << endl;
		cout << getTextFromField("Interface_Previous") << endl;
		break;

	default:
		break;
	}
}

void UpdateInterface::run()
{
	state = START_UPDATE;
	displayInterfaceText();
	string description = Interface::getAction();
	string label = Interface::getAction();

	state = START_ANALYSIS;
	displayInterfaceText();
	ModelImporter m(description, label);
	m.importModel();

	state = END_ANALYSIS;
	displayInterfaceText();
	getAction();
}