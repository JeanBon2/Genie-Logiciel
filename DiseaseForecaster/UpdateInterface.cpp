// System include
#include <iostream>
using namespace std;

// Personnal include
#include "UpdateInterface.h"
#include "Interface.h"
// Constants

// Constructors
UpdateInterface::UpdateInterface()
{

}


UpdateInterface::UpdateInterface(const UpdateInterface* x)
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
		cout << getTextFromField("UpdateInterface_Start") << endl;
		break;
	case START_EXPORT_ANALYSIS:
		cout << getTextFromField("UpdateInterface_Export") << endl;
		break;
	case START_IMPORT_MODEL:
		cout << getTextFromField("UpdateInterface_GetModels") << endl;
		break;
	case EXPORT_SUCCESS:
		cout << getTextFromField("UpdateInterface_Success") << endl;
		break;
	case EXPORT_FAIL:
		cout << getTextFromField("UpdateInterface_Fail") << endl;
		break;
	default:
		break;
	}
}

void UpdateInterface::run()
{
	state = START_UPDATE;
	displayInterfaceText();
	state = START_EXPORT_ANALYSIS;
	displayInterfaceText();
	state = START_IMPORT_MODEL;
	displayInterfaceText();
	state = EXPORT_SUCCESS;
	displayInterfaceText();
	system("pause");
	
}

bool UpdateInterface::startUpdate()
{
	return true;
}
bool UpdateInterface::exportAnalysis()
{
	return true;
}

string UpdateInterface::getAction()
{
	return "";
}
// Private methods
