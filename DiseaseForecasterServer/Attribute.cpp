// System include
#include <iostream>
using namespace std;

// Personnal include
#include "Attribute.h"

// Constants

// Constructors
Attribute::Attribute(const int id, const string name, const bool discrete) : id(id), name(name), discrete(discrete)
{
#ifdef DEBUG
	cout << "Attribute constructor call" << endl;
#endif // DEBUG
}
