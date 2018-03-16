//menu
// System include
using namespace std;
#include <string>
// Personnal include
#include "LeaveInterface.h"
#include "Log.h"

// Protected methods
void LeaveInterface::displayInterfaceText()
{
	cout << getTextFromField("Leave_App");
}

void LeaveInterface::run()
{
	displayInterfaceText();
}
