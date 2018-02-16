#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

// System include
#include <iostream>
using namespace std;

// Personnal include

// Constants

// Types

// Class
class Attribute
{
	// Attributes
protected:
	int id;
	string name;
	bool discrete;

	// Methods
public:
	// Constructors
	Attribute(const int id, const string& name, const bool discrete);

	// Destructors
	virtual ~Attribute();

	// Others
	int getId() const { return id; }
	string getName() const { return name; }
	bool isDiscrete() const { return discrete; }
};

#endif // ATTRIBUTE_H