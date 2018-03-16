#ifndef HELPINTERFACE_H
#define HELPINTERFACE_H
// System include

// Personnal include
#include "Interface.h"

// Class
class HelpInterface : public Interface
{
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
};

#endif // HELPINTERFACE_H
