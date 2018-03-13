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
	int id;
	string patientName;
	string doctorName;
	QDate printDate;
	int sensorId;

	// Methods
public:
	// Constructors
	HealthPrint(int id, string patientName, string doctorName, string printDate, int sensorId,
		map<string, double> continuousAttributesValues = map<string, double>(), map<string, string> discreteAttributesValues = map<string, string>());

	// Destructors
	~HealthPrint();

	//Others
	string displayContent(bool printOnScreen = true);
	string getPatientName();
	string getDoctorName();
	QDate getPrintDate();
	map<string, double> getContinuousAttributesValues();
	map<string, string> getDiscreteAttributesValues();
	int getId();
	int getSensorId();
};

#endif // HEALTHPRINT_H
