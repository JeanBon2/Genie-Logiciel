// System include
#include <iostream>
#include <string>
#include <utility>
using namespace std;

// Personnal include
#include "Disease.h"

// Constants

// Constructors
Disease::Disease(const int id, string name, vector<shared_ptr<Attribute>> discriminantAttributes) : id(id), name(
	                                                                                                    std::move(name)), discriminantAttributes(
	                                                                                                           std::move(
		                                                                                                           discriminantAttributes))
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

Disease* Disease::diseaseWithNameFromVector(string name, vector<Disease>& vec)
{
	for(auto&& disease : vec)
	{
		if (disease.getName() == name)
		{
			return &disease;
		}
	}
	return nullptr;
}
