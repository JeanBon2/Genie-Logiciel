#include <QtCore/QCoreApplication>
#include "CsvParser.h"
#include <iostream>
#include <Windows.h>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QFile description(R"(HealthMeasurementDescription.txt)");
	QFile measurement(R"(HealthMeasurements.txt)");
	QFile labels(R"(HealthMeasurementsWithLabels.txt)");

	return a.exec();
}
