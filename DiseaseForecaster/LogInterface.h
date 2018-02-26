#ifndef LOGINTERFACE_H
#define LOGINTERFACE_H
//MenuInt.h
// System include

// Personnal include
#include "Interface.h"

// Constants

// Types

// Class
class LogInterface : public Interface
{
	// Attributes
public:

protected:

private:

	// Methods
public:
	// Constructors
	LogInterface();
	LogInterface(const LogInterface* x);

	// Destructors
	~LogInterface();

	// Others

protected:
	void getInterfaceText();
	void run();

private:

};

#endif // LOGINTERFACE_H