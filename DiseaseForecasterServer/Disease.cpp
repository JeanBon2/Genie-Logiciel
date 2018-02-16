// System include
#include <iostream>
#include <string>
using namespace std;

// Personnal include
#include "Disease.h"

// Constants

// Constructors
Disease::Disease(const int id, const string& name, const vector<shared_ptr<Attribute>>&& discriminantAttributes) : id(id), name(name), discriminantAttributes(discriminantAttributes)
{
#ifdef DEBUG
	cout << "Disease constructor call" << endl;
#endif // DEBUG
}

// Destructor
Disease::~Disease()
{
#ifdef DEBUG
	cout << "Disease destructor call" << endl;
#endif // DEBUG
}

void Disease::addDiscriminantAttribute(shared_ptr<Attribute> attribute)
{
	discriminantAttributes.push_back(attribute);
}
bool Disease::isDiscriminant(shared_ptr<Attribute> attribute)
{
	for(auto&& discriminantAttribute : discriminantAttributes)
	{
		if (discriminantAttribute->getId() == attribute->getId())
		{
			return true;
		}
	}
	return false;
}
