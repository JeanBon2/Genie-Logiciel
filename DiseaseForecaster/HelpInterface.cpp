//menu
// System include
using namespace std;
#include <string>
// Personnal include
#include "HelpInterface.h"
#include "Log.h"

// Constants

// Constructors
HelpInterface::HelpInterface()
{
#ifdef DEBUG
	cout << "HelpInterface constructor call" << endl;
#endif // DEBUG
}

HelpInterface::HelpInterface(const HelpInterface* x)
{
#ifdef DEBUG
	cout << "Xxx copy constructor call" << endl;
#endif // DEBUG

}

// Destructor
HelpInterface::~HelpInterface()
{
#ifdef DEBUG
	cout << "Xxx destructor call" << endl;
#endif // DEBUG
}

// Public methods

// Protected methods
void HelpInterface::getInterfaceText()
{}


void HelpInterface::run()
{
	system("..\\DiseaseForecaster\\Ressources\\Manuel.pdf");
}