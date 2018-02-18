#ifndef CONTINUOUSATTRIBUTE_H
#define CONTINUOUSATTRIBUTE_H

// System include
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// Personnal include
#include "Attribute.h"

// Constants

// Types
typedef pair<double, double> interval;

// Class
class ContinuousAttribute : public Attribute
{
	// Attributes
private:
	vector<interval> normalIntervals;

	// Methods
public:
	// Constructors
	ContinuousAttribute(const int id, const string& name, const vector<interval>&& normalIntervals = vector<interval>() );

	// Destructors
	~ContinuousAttribute() override;

	// Others
	int getId() const { return id; }
	string getName() const { return name; }

	vector<interval> getNormalIntervals() const { return normalIntervals; }
	void addNormalInterval(const interval& normalInterval);
	bool isInNormalInterval(const double& value);
};

#endif // CONTINUOUSATTRIBUTE_H