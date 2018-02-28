#pragma once
#ifndef HEALTHPRINT_H
#define HEALTHPRINT_H

// System include
using namespace std;
#include <iostream>
#include <map>
#include <QDate>
#include <vector>

// Personnal include
#include "PotentialDisease.h"

// Class
class HealthPrint
{
	// Attributes
protected:
	map<string, double> attributes;
	string patientName;
	string doctorName;
	QDate printDate;
	int sensorId;

	// Methods
public:
	// Constructors
	HealthPrint(map<string, double> attributes, string patientName, string doctorName, string printDate, int snesorId);

	// Destructors
	~HealthPrint();

	//Others
	void displayContent();
	string getPatientName();
	QDate getPrintDate();

protected:
	void analyse();
};

#endif // HEALTHPRINT_H
