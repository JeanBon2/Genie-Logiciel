#include <QtCore/QCoreApplication>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "CsvParser.h"
#include "Disease.h"
#include <vector>
#include "DiscreteAttribute.h"
#include "ContinuousAttribute.h"
#include "DbManager.h"

using namespace std;

const string filePath = "export.json";

bool exportDatabase(vector<Disease>& diseases) {
	QFile file(QString::fromStdString(filePath));
	if (!file.open(QIODevice::WriteOnly))
	{
		// LOG
		return false;
	}
	QJsonDocument jsonDocument;
	QJsonArray diseaseList;
	for (auto&& disease : diseases)
	{
		QJsonObject diseaseJson;
		QJsonObject discriminantAttributesJson;
		QJsonArray discreteAttributes, continuousAttributes;
		diseaseJson.insert("id", disease.getId());
		diseaseJson.insert("name", QString::fromStdString(disease.getName()));
		for (auto&& attribute : disease.getDiscriminantAttributes())
		{
			QJsonObject attributeJson;
			attributeJson.insert("id", attribute->getId());
			attributeJson.insert("name", QString::fromStdString(attribute->getName()));
			if (attribute->isDiscrete())
			{
				QJsonArray normalValuesJson;
				shared_ptr<DiscreteAttribute> discreteAttribute = dynamic_pointer_cast<DiscreteAttribute>(attribute);
				
				for (auto&& normalValue : discreteAttribute->getNormalValues())
				{
					QJsonObject normalValueJson;
					normalValueJson.insert("valueName", QString::fromStdString(normalValue.first));
					normalValueJson.insert("value", normalValue.second);
					normalValuesJson.push_back(normalValueJson);
				}

				attributeJson.insert("normalValues", normalValuesJson);
				discreteAttributes.push_back(attributeJson);
			}
			else
			{
				QJsonArray normalIntervalsJson;
				shared_ptr<ContinuousAttribute> continuousAttribute = dynamic_pointer_cast<ContinuousAttribute>(attribute);

				for (auto&& normalInterval : continuousAttribute->getNormalIntervals())
				{
					QJsonObject normalIntervalJson;
					normalIntervalJson.insert("minimum", normalInterval.first);
					normalIntervalJson.insert("maximum", normalInterval.second);
					normalIntervalsJson.push_back(normalIntervalJson);
				}

				attributeJson.insert("normalIntervals", normalIntervalsJson);
				continuousAttributes.push_back(attributeJson);
			}
		}
		discriminantAttributesJson.insert("discreteAttributes", discreteAttributes);
		discriminantAttributesJson.insert("continuousAttributes", continuousAttributes);
		diseaseJson.insert("discriminantAttributes", discriminantAttributesJson);
		diseaseList.push_back(diseaseJson);
	}

	file.write(QJsonDocument(diseaseList).toJson());

	return true;
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QFile description(R"(HealthMeasurementDescription.txt)");
	QFile measurement(R"(HealthMeasurements.txt)");
	QFile labels(R"(HealthMeasurementsWithLabels.txt)");

	Disease tetanosDisease(1, "Tétanos");
	DiscreteAttribute discreteAttribute(1, "Yeux");
	discreteAttribute.addNormalValue({ "Bleu", 1 });
	discreteAttribute.addNormalValue({ "Rouge", 2 });
	const shared_ptr<DiscreteAttribute> discreteAttributePtr(&discreteAttribute);
	tetanosDisease.addDiscriminantAttribute(discreteAttributePtr);

	DiscreteAttribute discreteAttribute2(3, "Couleur de peau");
	discreteAttribute2.addNormalValue({ "Blanche", 1 });
	const shared_ptr<DiscreteAttribute> discreteAttributePtr2(&discreteAttribute2);
	tetanosDisease.addDiscriminantAttribute(discreteAttributePtr2);

	ContinuousAttribute continuousAttribute(2, "Poids");
	continuousAttribute.addNormalInterval({ 60, 80 });
	const shared_ptr<ContinuousAttribute> continuousAttributePtr(&continuousAttribute);
	tetanosDisease.addDiscriminantAttribute(continuousAttributePtr);

	DbManager db("DiseaseForecasterServer.db");
	vector<Disease> dl;
	dl.push_back(tetanosDisease);
	db.insertIntoDatabase(dl);

	auto&& diseaseList = db.getDiseases();
	exportDatabase(diseaseList);

	return a.exec();
}
