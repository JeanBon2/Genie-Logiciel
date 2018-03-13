// System include
#include <iostream>
#include <iterator>
#include <map>
#include <QDate>
#include <string>

using namespace std;

// Personnal include
#include "HealthPrint.h"

// Constants

// Constructors
HealthPrint::HealthPrint(int id, string patientName, string doctorName, string printDate, int sensorId,
	map<string, double> continuousAttributesValues, map<string, string> discreteAttributesValues) :
	id(id),patientName(patientName), doctorName(doctorName), sensorId(sensorId),
continuousAttributesValues(continuousAttributesValues), discreteAttributesValues(discreteAttributesValues)
{
	#ifdef DEBUG
		cout << "HealthPrint constructor call" << endl;
	#endif // DEBUG
		this->printDate = QDate::fromString(QString::fromStdString(printDate), "dd/MM/yyyy");//pas sur que ca fonctioone ^^
}

// Destructor
HealthPrint::~HealthPrint()
{
	#ifdef DEBUG
		cout << "HealthPrint destructor call" << endl;
	#endif // DEBUG
}
//Others
string HealthPrint::displayContent(bool printOnScreen)
{
	string message = "";

	message += "Sensor ID : " + to_string(sensorId) + "\n";
	message += "Print date : " + printDate.toString("dd.MM.yyyy").toStdString() + "\n"; // .toUtf8().constData()
	message += "Doctor name : " + doctorName + "\n";
	message += "Patient name : " + patientName + "\n";

	for (auto const& continuousAttributeValue : continuousAttributesValues)
	{
		message += continuousAttributeValue.first + " : " + to_string(continuousAttributeValue.second)+ "\n";
	}
	for (auto const& discreteAttributeValue : discreteAttributesValues)
	{
		message += discreteAttributeValue.first + " : " + discreteAttributeValue.second + "\n";
	}

	if (printOnScreen)
		cout << message;

	return message;
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
