// System include
#include <iostream>
using namespace std;

// Personnal include
#include "ContinuousAttribute.h"

// Constants

// Constructors
ContinuousAttribute::ContinuousAttribute(const int id, const string& name, const vector<interval>&& normalIntervals) : Attribute(id, name, false), normalIntervals(normalIntervals)
{
#ifdef DEBUG
	cout << "ContinuousAttribute constructor call" << endl;
#endif // DEBUG
}

void ContinuousAttribute::addNormalInterval(const interval& normalInterval)
{
	normalIntervals.push_back(normalInterval);
}
bool ContinuousAttribute::isInNormalInterval(const double& value)
{
	for(auto&& normalInterval : normalIntervals)
	{
		if (value >= normalInterval.first && value <= normalInterval.second)
		{
			return true;
		}
	}
	return false;
}
