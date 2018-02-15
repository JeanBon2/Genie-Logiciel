#ifndef SEARCHINTERFACE_H
#define SEARCHINTERFACE_H

// System include
using namespace std;
#include <iostream>
#include <vector>
#include <string>

// Personnal include
#include "Interface.h"
#include "HealthPrint.h"


// Constants

// Types

// Class
class SearchInterface : public Interface
{
	// Attributes
public:

protected:

private:
	unsigned short stage;
	vector<HealthPrint> resultsFromRequest;

	// Methods
public:
	// Constructors
	SearchInterface();

	// Destructors
	~SearchInterface();

	// Others

protected:

	void getInterfaceText();
	string getAction();
	void searchHealthPrint(string patientName);
	bool remove(unsigned int printNumber);
private:

};
#endif // SEARCHINTERFACE_H
