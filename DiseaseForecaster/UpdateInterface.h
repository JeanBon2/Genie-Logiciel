#ifndef UPDATEINTERFACE_H
#define UPDATEINTERFACE_H

// System include
#include <iostream>
#include <string>
using namespace std;

// Personnal include
#include "Interface.h"
// Constants

// Types

// Class
class UpdateInterface : public Interface
{
	// Attributes
public:
	

protected:
	

private:
	const enum updateState
	{
		START_UPDATE,
		START_EXPORT_ANALYSIS,
		START_IMPORT_MODEL,
		EXPORT_SUCCESS,
		EXPORT_FAIL
	};
	updateState state;

	// Methods
public:
	// Constructors
	UpdateInterface();
	UpdateInterface(const UpdateInterface* x);

	// Destructors
	~UpdateInterface();

	// Others
	

protected:
	void displayInterfaceText();
	string getAction();
	bool startUpdate();
	bool exportAnalysis();

private:
	void run();
};

#endif // UPDATEINTERFACE_H