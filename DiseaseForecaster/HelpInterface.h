#ifndef HELPINTERFACE_H
#define HELPINTERFACE_H
// System include

// Personnal include
#include "Interface.h"

// Constants

// Types

// Class
class HelpInterface : public Interface
{
	// Attributes
public:

protected:

private:

	// Methods
public:
	// Constructors
	HelpInterface();
	HelpInterface(const HelpInterface* x);

	// Destructors
	~HelpInterface();

	// Others

protected:
	void displayInterfaceText();
	void run();

private:

};

#endif // HELPINTERFACE_H