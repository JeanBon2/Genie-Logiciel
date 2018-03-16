#ifndef DISCRETEATTRIBUTE_H
#define DISCRETEATTRIBUTE_H

// System include
#include <vector>
#include <memory>
using namespace std;

// Personnal include
#include "Attribute.h"

// Constants

// Types

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
	bool removeNormalValue(const string& normalValue);
	bool isInNormalValues(const string& value);

	static shared_ptr<DiscreteAttribute> attributeWithNameFromVector(string name, vector<shared_ptr<DiscreteAttribute>>& vec);
};

#endif // DISCRETEATTRIBUTE_H
