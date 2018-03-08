// System include
#include <iostream>
#include <QFile>
#include <qjsondocument.h>
#include <qjsonarray.h>
using namespace std;

// Personnal include
#include "UpdateInterface.h"
#include "Interface.h"
// Constants

// Constructors
UpdateInterface::UpdateInterface()
{

}


UpdateInterface::UpdateInterface(const UpdateInterface* x)
{
#ifdef DEBUG
	cout << "UpdateInterface copy constructor call" << endl;
#endif // DEBUG
}

// Destructor
UpdateInterface::~UpdateInterface()
{
#ifdef DEBUG
	cout << "UpdateInterface destructor call" << endl;
#endif // DEBUG
}

// Public methods

// Protected methods
void UpdateInterface::displayInterfaceText()
{
	switch (state)
	{
	case START_UPDATE:
		cout << getTextFromField("UpdateInterface_Start") << endl;
		break;
	case START_EXPORT_ANALYSIS:
		cout << getTextFromField("UpdateInterface_Export") << endl;
		break;
	case START_IMPORT_MODEL:
		cout << getTextFromField("UpdateInterface_GetModels") << endl;
		break;
	case EXPORT_SUCCESS:
		cout << getTextFromField("UpdateInterface_Success") << endl;
		break;
	case EXPORT_FAIL:
		cout << getTextFromField("UpdateInterface_Fail") << endl;
		break;
	default:
		break;
	}
}

void UpdateInterface::run()
{
	state = START_UPDATE;
	displayInterfaceText();
	state = START_EXPORT_ANALYSIS;
	displayInterfaceText();
	state = START_IMPORT_MODEL;
	displayInterfaceText();
	state = EXPORT_SUCCESS;
	displayInterfaceText();

	/*
	QJsonObject test = getJsonContent();
	getAttributesValues(test);

	for (auto &i : discretesValuesData) {
	cout << "------------------------"<<endl;
	cout << i->attributeId << endl;
	cout << i->normalValue << endl;
	cout << "------------------------";
	}
	*/

	system("pause");

}

bool UpdateInterface::startUpdate()
{

	return true;
}
bool UpdateInterface::exportAnalysis()
{
	return true;
}

string UpdateInterface::getAction()
{
	return "";
}
// Private methods
QJsonObject UpdateInterface::getJsonContent()
{
	QString jsonFileContent;
	QFile file;
	file.setFileName("export.json");
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	jsonFileContent = file.readAll();
	file.close();
	QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonFileContent.toUtf8());
	QJsonObject jsonObject = jsonDocument.object();
	return jsonObject;
}

void UpdateInterface::getAttributeContent(QJsonObject jsonObject) {

	QJsonObject allAttributes = jsonObject["attributes"].toObject();

	QJsonArray continuousAttributesArray = allAttributes["continuousAttributes"].toArray();
	QJsonArray discreteAttributesArray = allAttributes["discreteAttributes"].toArray();

	for (auto && continuousAttribute : continuousAttributesArray)
	{
		attributeContent *attrib = new attributeContent();
		attrib->id = continuousAttribute.toObject().value(QString("id")).toInt();
		attrib->name = continuousAttribute.toObject().value(QString("name")).toString().toStdString();
		attrib->discrete = 0;
		attributesData.push_back(attrib);
	}
	for (auto && discreteAttributes : discreteAttributesArray)
	{
		attributeContent *attrib = new  attributeContent();
		attrib->id = discreteAttributes.toObject().value(QString("id")).toInt();
		attrib->name = discreteAttributes.toObject().value(QString("name")).toString().toStdString();
		attrib->discrete = 1;
		attributesData.push_back(attrib);
	}

}

//Description : Rempli les vecteurs diseaseContent et discriminantDiseaseContent
void UpdateInterface::getDiseasesContent(QJsonObject jsonObject) {

	QJsonArray allDiseases = jsonObject["diseases"].toArray();
	for (auto && disease : allDiseases)
	{
		int i = 0;
		diseaseContent *diseasePtr = new diseaseContent();
		diseasePtr->id = disease.toObject().value(QString("id")).toInt();
		diseasePtr->name = disease.toObject().value(QString("name")).toString().toStdString();
		diseasesData.push_back(diseasePtr);

		QJsonArray discriminantAttributeJsonArray = disease.toObject()["discriminantAttributes"].toArray();
		for (i = 0; i<discriminantAttributeJsonArray.count(); i++)
		{
			discriminantAttributesContent *structDiscriminantAttrib = new discriminantAttributesContent();
			structDiscriminantAttrib->diseaseId = disease.toObject().value(QString("id")).toInt();
			structDiscriminantAttrib->attributeId = discriminantAttributeJsonArray[i].toInt();
			discriminantDiseasesData.push_back(structDiscriminantAttrib);
		}
	}
}

void UpdateInterface::getAttributesValues(QJsonObject jsonObject) {

	int i;
	QJsonObject allAttributes = jsonObject["attributes"].toObject();

	QJsonArray continuousAttributesArray = allAttributes["continuousAttributes"].toArray();
	QJsonArray discreteAttributesArray = allAttributes["discreteAttributes"].toArray();

	for (auto && continuousAttribute : continuousAttributesArray)
	{
		QJsonArray intervalAttributeArray = continuousAttribute.toObject()["normalIntervals"].toArray();
		for (auto && intervalAttribute : intervalAttributeArray)
		{
			continuousValuesContent *continuousVal = new continuousValuesContent();
			continuousVal->attributeId = continuousAttribute.toObject().value(QString("id")).toInt();
			continuousVal->minimumValue = intervalAttribute.toObject().value(QString("minimum")).toDouble();
			continuousVal->maximumValue = intervalAttribute.toObject().value(QString("maximum")).toDouble();
			continuousValuesData.push_back(continuousVal);
		}
	}

	for (auto && discreteAttribute : discreteAttributesArray)
	{
		QJsonArray normalValuesArray = discreteAttribute.toObject()["normalValues"].toArray();

		for (i = 0; i<normalValuesArray.count(); i++)
		{
			discretesValuesContent *normalValPtr = new discretesValuesContent();
			normalValPtr->attributeId = discreteAttribute.toObject().value(QString("id")).toInt();
			normalValPtr->normalValue = normalValuesArray[i].toString().toStdString();

			discretesValuesData.push_back(normalValPtr);
		}
	}
	/*
	struct discretesValuesContent {
	int attributeId;
	string normalValue;
	};
	*/
}