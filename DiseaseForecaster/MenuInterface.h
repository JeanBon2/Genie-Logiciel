#ifndef MENUINTERFACE_H
#define MENUINTERFACE_H

// System include
using namespace std;
#include <iostream>
#include <string>

// Personnal include
#include "Interface.h"

// Class
class MenuInterface : public Interface
{
	// Methods
protected:
	void displayInterfaceText();
	void run();
};

#endif // MENUINTERFACE_H
