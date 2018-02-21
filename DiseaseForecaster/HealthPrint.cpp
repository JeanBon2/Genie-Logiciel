// System include
#include <iostream>
#include <iterator>
#include <QDate>
using namespace std;

// Personnal include
#include "HealthPrint.h"

// Constants

// Constructors
HealthPrint::HealthPrint(map<string, double> attributes, string patientName, string doctorName, string printDate, int sensorId) : 
	attributes(attributes), patientName(patientName), doctorName(doctorName), sensorId(sensorId)
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
	
	for (auto const& attribute : attributes)
	{
		cout << attribute.first << " : " << attribute.second << endl;
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
