#ifndef DISEASE_H
#define DISEASE_H

// System include
#include <iostream>
#include <vector>
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
	vector<Attribute*> discriminantAttributes;

	// Methods
public:
	// Constructors
	Disease(const int id, const string& name, const vector<Attribute*>&& discriminantAttributes = vector<Attribute*>());

	// Destructors
	~Disease();

	// Others
	int getId() const { return id; }
	string getName() const { return name; }

	vector<Attribute*> getDiscriminantAttributes() const { return discriminantAttributes; }
	void addDiscriminantAttribute(Attribute* attribute);
	bool isDiscriminant(Attribute* attribute);
};

#endif // DISEASE_H