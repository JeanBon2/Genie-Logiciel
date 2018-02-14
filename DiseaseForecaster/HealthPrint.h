#pragma once
#ifndef HEALTHPRINT_H
#define HEALTHPRINT_H

// System include
using namespace std;
#include <iostream>
#include <map>
#include <time.h>

// Class
class HealthPrint
{
	// Attributes
private:
	map<string, double> attributes;
	string patientName;
	string doctorName;
	time_t printDate;
	int sensorId;

	// Methods
public:
	// Constructors
	HealthPrint(map<string, double> attributes, string patientName, string doctorName, time_t printDate, int snesorId);

	// Destructors
	~HealthPrint();

protected:
	void analyse();
};

#endif // HEALTHPRINT_H
