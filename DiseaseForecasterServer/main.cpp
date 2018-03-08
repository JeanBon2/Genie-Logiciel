#include <QtCore/QCoreApplication>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <algorithm>
#include <vector>

#include "CsvParser.h"
#include "Disease.h"
#include "DiscreteAttribute.h"
#include "ContinuousAttribute.h"
#include "DbManager.h"
#include "ModelImporter.h"

using namespace std;

const string filePath = "export.json";

bool exportDatabase(vector<Disease>& diseases, vector<shared_ptr<Attribute>> attributes) {
	QFile file(QString::fromStdString(filePath));
	if (!file.open(QIODevice::WriteOnly))
	{
		// LOG
		return false;
	}
	QJsonDocument jsonDocument;
	QJsonArray diseaseList;
	QJsonObject discriminantAttributesJson;
	QJsonArray discreteAttributes, continuousAttributes;
	for (auto&& disease : diseases)
	{
		QJsonObject diseaseJson;
		QJsonArray discriminantAttributesJsonForDisease;
		diseaseJson.insert("id", disease.getId());
		diseaseJson.insert("name", QString::fromStdString(disease.getName()));
		for (auto&& attribute : disease.getDiscriminantAttributes())
		{
			discriminantAttributesJsonForDisease.push_back(attribute->getId());
		}
		diseaseJson.insert("discriminantAttributes", discriminantAttributesJsonForDisease);
		diseaseList.push_back(diseaseJson);
	}

	for (auto&& attribute : attributes)
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
				QJsonValue normalValueJson(QString::fromStdString(normalValue));
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

	QJsonObject document;
	document.insert("diseases", diseaseList);
	document.insert("attributes", discriminantAttributesJson);

	file.write(QJsonDocument(document).toJson());

	return true;
}
bool importModel(const string& descriptionPath, const string& healtphrintsPath)
{
	//QFile descriptionFile(QString::fromStdString(descriptionPath));
	//vector<vector<string>> attributes = CsvParser::staticParse(descriptionPath);
	//if (attributes.empty())
	//{
	//	// LOG
	//	return false;
	//}
	//vector<string>& descriptions = attributes[0];
	//attributes.erase(attributes.begin());
	//if (descriptions.size() != 2)
	//{
	//	// LOG
	//	return false;
	//}

	//string& attributeNameHeader = descriptions[0];
	//string& attributeTypeHeader = descriptions[1];
	//std::transform(attributeNameHeader.begin(), attributeNameHeader.end(), attributeNameHeader.begin(), ::tolower);
	//std::transform(attributeTypeHeader.begin(), attributeTypeHeader.end(), attributeTypeHeader.begin(), ::tolower);
	//if (attributeNameHeader != "AttributeName" || attributeTypeHeader != "AttributeType")
	//{
	//	// LOG
	//	return false;
	//}


	//map<string, vector<double>> continuousAttributes;
	//map<string, vector<string>> discreteAttributes;
	//
	//for (auto&& line : attributes)
	//{
	//	if (line.size() != 2)
	//	{
	//		// LOG
	//		return false;
	//	}

	//	const string& attributeName = line[0];
	//	const string& attributeType = line[1];
	//	std::transform(attributeType.begin(), attributeType.end(), attributeType.begin(), ::tolower);

	//	if (line[1] == "string")
	//	{
	//		// Attribut discret
	//		discreteAttributes.emplace(attributeName, vector<string>());
	//	} else
	//	{
	//		// Attribut continu
	//		continuousAttributes.emplace(attributeName, vector<double>());
	//	}
	//}


	return true;
}

int main(int argc, char *argv[])
{
	/*QFile description(R"(HealthMeasurementDescription.txt)");
	QFile measurement(R"(HealthMeasurements.txt)");
	QFile labels(R"(HealthMeasurementsWithLabels.txt)");

	Disease tetanosDisease(1, "Tetanos");
	Disease rubeoleDisease(2, "Rubeole");
	DiscreteAttribute discreteAttribute(1, "Yeux");
	discreteAttribute.addNormalValue("Bleu");
	discreteAttribute.addNormalValue("Rouge");
	const shared_ptr<DiscreteAttribute> discreteAttributePtr(&discreteAttribute);
	tetanosDisease.addDiscriminantAttribute(discreteAttributePtr);
	rubeoleDisease.addDiscriminantAttribute(discreteAttributePtr);

	DiscreteAttribute discreteAttribute2(3, "Couleur de peau");
	discreteAttribute2.addNormalValue("Blanche");
	const shared_ptr<DiscreteAttribute> discreteAttributePtr2(&discreteAttribute2);
	tetanosDisease.addDiscriminantAttribute(discreteAttributePtr2);

	ContinuousAttribute continuousAttribute(2, "Poids");
	continuousAttribute.addNormalInterval({ 60, 80 });
	const shared_ptr<ContinuousAttribute> continuousAttributePtr(&continuousAttribute);
	tetanosDisease.addDiscriminantAttribute(continuousAttributePtr);

	DbManager db("DiseaseForecasterServer.db");
	vector<Disease> dl;
	dl.push_back(tetanosDisease);
	dl.push_back(rubeoleDisease);
	db.insertIntoDatabase(dl);

	auto&& diseaseList = db.getDiseases();
	auto&& attributeList = db.getAttributes();
	exportDatabase(diseaseList, attributeList);*/

	ModelImporter m("HealthMeasurementDescription.txt", "HealthMeasurementsWithLabels.txt");
	if (m.importModel())
	{
		cout << "Ca plante pas tout de suite !" << endl;
	} else
	{
		cout << "Ah ben si..." << endl;
	}

	return EXIT_SUCCESS;
}
