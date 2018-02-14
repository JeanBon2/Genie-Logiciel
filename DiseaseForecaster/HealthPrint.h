#pragma once
#ifndef HEALTHPRINT_H
#define HEALTHPRINT_H

// System include
using namespace std;
#include <iostream>
#include <map>
#include <QDateTime>

// Class
class HealthPrint
{
	// Attributes
private:
	map<string, double> attributes;
	string patientName;
	string doctorName;
	QDateTime printDate;
	int sensorId;

	// Methods
public:
	// Constructors
	HealthPrint(map<string, double> attributes, string patientName, string doctorName, QDateTime printDate, int snesorId);

	// Destructors
	~HealthPrint();

protected:
	void analyse();
};

#endif // HEALTHPRINT_H
