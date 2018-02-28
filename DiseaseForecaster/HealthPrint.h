#pragma once
#ifndef HEALTHPRINT_H
#define HEALTHPRINT_H

// System include
using namespace std;
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
	map<string, double> continuousAttributesValues;
	map<string, string> discreteAttributesValues;
	string patientName;
	string doctorName;
	QDate printDate;
	int sensorId;

	// Methods
public:
	// Constructors
	HealthPrint(map<string, double> continuousAttributesValues, map<string, string> discreteAttributesValues,
				string patientName, string doctorName, string printDate, int sensorId);

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
