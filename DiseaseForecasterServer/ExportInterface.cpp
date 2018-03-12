// System include
#include <iostream>
#include <string>
#include <QFile>
#include <qjsondocument.h>
#include <qjsonarray.h>
using namespace std;

// Personnal include
#include "ExportInterface.h"
#include "Interface.h"
#include "DbManager.h"
#include "Log.h"
// Constants

// Constructors
ExportInterface::ExportInterface()
{

}


ExportInterface::ExportInterface(const ExportInterface*)
{
#ifdef DEBUG
	cout << "UpdateInterface copy constructor call" << endl;
#endif // DEBUG
}

// Destructor
ExportInterface::~ExportInterface()
{
#ifdef DEBUG
	cout << "UpdateInterface destructor call" << endl;
#endif // DEBUG
}

// Public methods

// Protected methods
void ExportInterface::displayInterfaceText()
{
	switch (state)
	{
	case START_EXPORT:
		cout << getTextFromField("ExportInterface_ExportDone") << endl;
		break;

	case END_EXPORT:
		cout << getTextFromField("Interface_Previous") << endl;
		break;
	default:
		break;
	}
	
}

void ExportInterface::run()
{	
	state = START_EXPORT;
	DbManager db("DiseaseForecasterServer.db");
	exportDatabase(db.getDiseases(), db.getAttributes());
	displayInterfaceText();

	state = END_EXPORT;
	displayInterfaceText();
	getAction();
}
//private Methods
bool ExportInterface::exportDatabase(vector<Disease>&& diseases, vector<shared_ptr<Attribute>>&& attributes) 
{
	const string filePath = "export.json";
	QFile file(QString::fromStdString(filePath));
	if (!file.open(QIODevice::WriteOnly))
	{
		Log::info("Error while exporting database : file isn't writable.");
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