#ifndef MENUINTERFACE_H
#define MENUINTERFACE_H

// System include
using namespace std;
#include <iostream>
#include <string>

// Personnal include
#include "Interface.h"

// Constants

// Types

// Class
class MenuInterface : public Interface
{
	// Attributes
public:
	
protected:

private:
	
	// Methods
public:
	// Constructors
	MenuInterface();
	MenuInterface(const MenuInterface* x);

	// Destructors
	~MenuInterface();

	// Others

protected:
	void getInterfaceText();

	const string getAction();

private:

};

#endif // XXX_H