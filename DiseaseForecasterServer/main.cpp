#include <QtCore/QCoreApplication>
#include "CsvParser.h"
#include "Disease.h"
#include <vector>
#include "DiscreteAttribute.h"
#include "ContinuousAttribute.h"
#include "DbManager.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QFile description(R"(HealthMeasurementDescription.txt)");
	QFile measurement(R"(HealthMeasurements.txt)");
	QFile labels(R"(HealthMeasurementsWithLabels.txt)");

	Disease disease(1, "Tétanos");
	DiscreteAttribute discreteAttribute(1, "Yeux");
	discreteAttribute.addNormalValue({ "Bleu", 1 });
	discreteAttribute.addNormalValue({ "Rouge", 2 });
	disease.addDiscriminantAttribute(&discreteAttribute);

	ContinuousAttribute continuousAttribute(2, "Poids");
	continuousAttribute.addNormalInterval({ 60, 80 });
	disease.addDiscriminantAttribute(&continuousAttribute);

	DbManager db("DiseaseForecasterServer.db");
	db.insertIntoDatabase(vector<Disease>{disease});

	return a.exec();
}
