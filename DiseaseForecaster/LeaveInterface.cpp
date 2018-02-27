//menu
// System include
using namespace std;
#include <string>
// Personnal include
#include "LeaveInterface.h"
#include "Log.h"

// Constants

// Constructors
LeaveInterface::LeaveInterface()
{
#ifdef DEBUG
	cout << "LeaveInterface constructor call" << endl;
#endif // DEBUG
}

LeaveInterface::LeaveInterface(const LeaveInterface* x)
{
#ifdef DEBUG
	cout << "Xxx copy constructor call" << endl;
#endif // DEBUG

}

// Destructor
LeaveInterface::~LeaveInterface()
{
#ifdef DEBUG
	cout << "Xxx destructor call" << endl;
#endif // DEBUG
}

// Public methods

// Protected methods
void LeaveInterface::displayInterfaceText()
{
	cout << getTextFromField("Leave_App");
}


void LeaveInterface::run()
{
	displayInterfaceText();
}