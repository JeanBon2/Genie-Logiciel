#ifndef DISCRETEATTRIBUTE_H
#define DISCRETEATTRIBUTE_H

// System include
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// Personnal include
#include "Attribute.h"

// Types
typedef pair<string, double> value;

// Class
class DiscreteAttribute : public Attribute
{
	// Attributes
private:
	vector<string> normalValues;

	// Methods
public:
	// Constructors
    DiscreteAttribute(const int id, const string& name, const vector<string>&& normalValues = vector<string>());

	// Others
	int getId() const { return id; }
	string getName() const { return name; }

	vector<string> getNormalValues() const { return normalValues; }
	void addNormalValue(const string& normalValue);
	bool isInNormalValues(const string& value);
};

#endif // DISCRETEATTRIBUTE_H
