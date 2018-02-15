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
class DiscreteAttribute : public Attribute
{
	// Attributes
private:
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

	vector<value> getNormalValues() const { return normalValues; }
	void addNormalValue(const value& normalValue);
	bool isInNormalValues(const value& value);
};

#endif // DISCRETEATTRIBUTE_H