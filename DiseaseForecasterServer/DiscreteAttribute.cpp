// System include
#include <iostream>
using namespace std;

// Personnal include
#include "DiscreteAttribute.h"

// Constants

// Constructors
DiscreteAttribute::DiscreteAttribute(const int id, const string& name, const vector<string>&& normalValues) : Attribute(id, name, true), normalValues(normalValues)
{
#ifdef DEBUG
	cout << "DiscreteAttribute constructor call" << endl;
#endif // DEBUG
}

// Destructor
DiscreteAttribute::~DiscreteAttribute()
{
#ifdef DEBUG
	cout << "DiscreteAttribute destructor call" << endl;
#endif // DEBUG
}

// Public methods
void DiscreteAttribute::addNormalValue(const string& normalValue)
{
	normalValues.push_back(normalValue);
}
bool DiscreteAttribute::isInNormalValues(const string& value)
{
	for (auto&& normalValue : normalValues)
	{
		if (normalValue == value)
		{
			return true;
		}
	}
	return false;
}