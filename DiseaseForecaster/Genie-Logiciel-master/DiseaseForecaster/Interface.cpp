// System include
using namespace std;
#include <iostream>

// Personnal include
#include "Interface.h"

// Constants

// Constructors
Interface::Interface()
{
#ifdef DEBUG
	cout << "Xxx constructor call" << endl;
#endif // DEBUG
}

Interface::Interface(const Interface* x)
{
#ifdef DEBUG
	cout << "Xxx copy constructor call" << endl;
#endif // DEBUG
}

// Destructor
Interface::~Interface()
{
#ifdef DEBUG
	cout << "Xxx destructor call" << endl;
#endif // DEBUG
}

// Public methods


// Protected methods
void Interface::previous()
{

}

string Interface::getText(string keyMessage)
{

}


string Interface::getInterfaceText()
{

}

string Interface::getAction()
{

}

void Interface::createInterface(int interfaceID)
{

}
// Private methods
