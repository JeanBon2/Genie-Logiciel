// System include
#include <iostream>
#include <iterator>
#include <map>
#include <QDate>

using namespace std;

// Personnal include
#include "HealthPrint.h"

// Constants

// Constructors
HealthPrint::HealthPrint(map<string, double> continuousAttributesValues, map<string, string> discreteAttributesValues,
	string patientName, string doctorName, string printDate, int sensorId) :
	continuousAttributesValues(continuousAttributesValues), discreteAttributesValues(discreteAttributesValues), 
	patientName(patientName), doctorName(doctorName), sensorId(sensorId)
{
	#ifdef DEBUG
		cout << "HealthPrint constructor call" << endl;
	#endif // DEBUG
		this->printDate = QDate::fromString(QString::fromStdString(printDate), "dd/MM/yyyy");
}

// Destructor
HealthPrint::~HealthPrint()
{
	#ifdef DEBUG
		cout << "HealthPrint destructor call" << endl;
	#endif // DEBUG
}
//Others
void HealthPrint::displayContent()
{
	cout << "Sensor ID : " << sensorId << endl;
	cout << "Print date : " << printDate.toString("dd.MM.yyyy").toUtf8().constData() << endl;
	cout << "Doctor name :" << doctorName << endl;
	cout << "Patient name : " << patientName << endl;
	
	for (auto const& continuousAttributeValue : continuousAttributesValues)
	{
		cout << continuousAttributeValue.first << " : " << continuousAttributeValue.second << endl;
	}
	for (auto const& discreteAttributeValue : discreteAttributesValues)
	{
		cout << discreteAttributeValue.first << " : " << discreteAttributeValue.second << endl;
	}
}

string HealthPrint::getPatientName()
{
	return patientName;
}
QDate HealthPrint::getPrintDate()
{
	return printDate;
}

// Protected methods
void HealthPrint::analyse()
{

}
