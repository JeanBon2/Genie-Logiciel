// System include
#include <iostream>
using namespace std;

// Personnal include
#include "HealthPrint.h"

// Constants

// Constructors
HealthPrint::HealthPrint(map<string, double> attributes, string patientName, string doctorName, time_t printDate, int sensorId) : attributes(attributes), patientName(patientName), doctorName(doctorName), printDate(printDate), sensorId(sensorId)
{
	#ifdef DEBUG
		cout << "HealthPrint constructor call" << endl;
	#endif // DEBUG
}

// Destructor
HealthPrint::~HealthPrint()
{
	#ifdef DEBUG
		cout << "HealthPrint destructor call" << endl;
	#endif // DEBUG
}

// Protected methods
void HealthPrint::analyse()
{

}
