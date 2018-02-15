#ifndef DISCRETEATTRIBUTE_H
#define DISCRETEATTRIBUTE_H

// System include
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// Personnal include
#include "Attribute.h"

// Constants

// Types
typedef pair<string, double> value;

// Class
class DiscreteAttribute : Attribute
{
	// Attributes
private:
	int id;
	string name;
	vector<value> normalValues;

	// Methods
public:
	// Constructors
	DiscreteAttribute(const int id, const string& name, const vector<value>&& normalValues = vector<value>());

	// Destructors
	~DiscreteAttribute();

	// Others
	int getId() const { return id; }
	string getName() const { return name; }

	void addNormalValue(const value& normalValue);
	bool isInNormalValues(const value& value);
};

#endif // DISCRETEATTRIBUTE_H