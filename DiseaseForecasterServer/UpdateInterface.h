#ifndef UPDATEINTERFACE_H
#define UPDATEINTERFACE_H

// System include
#include <iostream>
#include <string>
#include <QJsonObject>
#include <vector>
#include <map>
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
		START_ANALYSIS,
		END_ANALYSIS
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

private:
	void run();
};

#endif // UPDATEINTERFACE_H