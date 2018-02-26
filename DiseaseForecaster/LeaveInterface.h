#ifndef LEAVEINTERFACE_H
#define LEAVEINTERFACE_H
//MenuInt.h
// System include

// Personnal include
#include "Interface.h"

// Constants

// Types

// Class
class LeaveInterface : public Interface
{
	// Attributes
public:

protected:

private:

	// Methods
public:
	// Constructors
	LeaveInterface();
	LeaveInterface(const LeaveInterface* x);

	// Destructors
	~LeaveInterface();

	// Others

protected:
	void getInterfaceText();
	void run();

private:

};

#endif // LEAVEINTERFACE_H