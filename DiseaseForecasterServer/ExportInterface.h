#ifndef EXPORTINTERFACE_H
#define EXPORTINTERFACE_H

// System include
#include <iostream>
#include <string>
#include <QJsonObject>
#include <vector>
#include <map>
#include "Disease.h"
using namespace std;

// Personnal include
#include "Interface.h"
// Constants

// Types

// Class
class ExportInterface : public Interface
{
	// Attributes
public:


protected:


private:
	const enum exportState
	{
		START_EXPORT,
		END_EXPORT,
	};
	exportState state;
	

	// Methods
public:
	// Constructors
	ExportInterface();
	ExportInterface(const ExportInterface* x);

	// Destructors
	~ExportInterface();

	// Others


protected:
	void displayInterfaceText();

private:
	bool exportDatabase(vector<Disease>&& diseases, vector<shared_ptr<Attribute>>&& attributes);
	void run();
};

#endif // EXPORTINTERFACE_H