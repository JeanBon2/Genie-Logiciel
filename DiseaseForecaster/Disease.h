#ifndef DISEASE_H
#define DISEASE_H

// System include
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Personnal include
#include "Attribute.h"
#include "DiscreteAttribute.h"
#include "ContinuousAttribute.h"
// Constants

// Types

// Class
class Disease
{
	// Attributes
private:
	int id;
	string name;
	vector<shared_ptr<Attribute>> discriminantAttributes;

	// Methods
public:
	// Constructors
	Disease(const int id, const string& newName, const vector<shared_ptr<Attribute>> discriminantAttributes = vector<shared_ptr<Attribute>>());

	// Destructors
	~Disease();

	// Others
	int getId() const { return id; }
	string getName() const { return name; }

	vector<shared_ptr<Attribute>> getDiscriminantAttributes() const { return discriminantAttributes; }
	void addDiscriminantAttribute(shared_ptr<Attribute> attribute);
	bool isDiscriminant(shared_ptr<Attribute> attribute);
	bool isDiscriminant(string id);
};

#endif // DISEASE_H
