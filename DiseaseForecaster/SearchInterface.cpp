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
