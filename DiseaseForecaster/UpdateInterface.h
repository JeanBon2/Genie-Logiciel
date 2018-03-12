#ifndef UPDATEINTERFACE_H
#define UPDATEINTERFACE_H

// System include
#include <iostream>
#include <string>
#include <QJsonObject>
#include <vector>
#include <map>
using namespace std;

// Personnal include
#include "Interface.h"
// Constants

// Types

// Class
class UpdateInterface : public Interface
{
	// Attributes
public:
	struct attributeContent {
		int id;
		string name;
		int discrete;
	};
	struct diseaseContent {
		int id;
		string name;
	};
	struct discriminantAttributesContent {
		int diseaseId;
		int attributeId;
	};
	struct continuousValuesContent {
		int attributeId;
		double minimumValue;
		double maximumValue;
	};
	struct discretesValuesContent {
		int attributeId;
		string normalValue;
	};


protected:


private:
	const enum updateState
	{
		START_UPDATE,
		START_EXPORT_ANALYSIS,
		START_IMPORT_MODEL,
		EXPORT_SUCCESS,
		EXPORT_FAIL
	};
	updateState state;


	vector<attributeContent*> attributesData;
	vector<diseaseContent*> diseasesData;
	vector<discriminantAttributesContent*> discriminantDiseasesData;
	vector<continuousValuesContent*> continuousValuesData;
	vector<discretesValuesContent*> discretesValuesData;

	// Methods
public:
	// Constructors
	UpdateInterface();
	UpdateInterface(const UpdateInterface* x);

	// Destructors
	~UpdateInterface();

	// Others
	vector<attributeContent*> getAttributeContent()
	{
		return attributesData;
	}

protected:
	void displayInterfaceText();
	string getAction();
	bool startUpdate();
	bool exportAnalysis();

private:
	void run();
	QJsonObject getJsonContent();
	void getAttributeContent(QJsonObject jsonObject);
	void getDiseasesContent(QJsonObject jsonObject);
	void getAttributesValues(QJsonObject jsonObject);
};

#endif // UPDATEINTERFACE_H