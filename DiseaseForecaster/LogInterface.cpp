//menu
// System include
using namespace std;
#include <string>
// Personnal include
#include "LogInterface.h"
#include "Log.h"

// Constants

// Constructors
LogInterface::LogInterface()
{
#ifdef DEBUG
	cout << "LogInterface constructor call" << endl;
#endif // DEBUG
}

LogInterface::LogInterface(const LogInterface* x)
{
#ifdef DEBUG
	cout << "Xxx copy constructor call" << endl;
#endif // DEBUG

}

// Destructor
LogInterface::~LogInterface()
{
#ifdef DEBUG
	cout << "Xxx destructor call" << endl;
#endif // DEBUG
}

// Public methods

// Protected methods
void LogInterface::getInterfaceText()
{}


void LogInterface::run()
{
	system("..\\DiseaseForecaster\\Ressources\\forecaster.log");
}