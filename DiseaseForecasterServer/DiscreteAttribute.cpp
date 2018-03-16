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

// Public methods
void DiscreteAttribute::addNormalValue(const string& normalValue)
{
	removeNormalValue(normalValue);
	normalValues.push_back(normalValue);
}

bool DiscreteAttribute::removeNormalValue(const string& normalValue)
{
	for(auto&& valueIterator = normalValues.begin(); valueIterator != normalValues.end();)
	{
		if (*valueIterator == normalValue)
		{
			normalValues.erase(valueIterator);
			return true;
		}
		++valueIterator;
	}
	return false;
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

shared_ptr<DiscreteAttribute> DiscreteAttribute::attributeWithNameFromVector(string name,
	vector<shared_ptr<DiscreteAttribute>> & vec)
{
	for (auto&& attribute : vec)
	{
		if (attribute->getName() == name)
		{
			return attribute;
		}
	}
	return nullptr;
}
