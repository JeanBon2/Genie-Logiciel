// System include
#include <iostream>
using namespace std;

// Personnal include
#include "DiscreteAttribute.h"

// Constants

// Constructors
DiscreteAttribute::DiscreteAttribute(const int id, const string& name, const vector<value>&& normalValues) : Attribute(id, name, true), normalValues(normalValues)
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
void DiscreteAttribute::addNormalValue(const value& normalValue)
{
	normalValues.push_back(normalValue);
}
bool DiscreteAttribute::isInNormalValues(const value& value)
{
	for (auto&& normalValue : normalValues)
	{
		if (normalValue.first == value.first && normalValue.second == value.second)
		{
			return true;
		}
	}
	return false;
}