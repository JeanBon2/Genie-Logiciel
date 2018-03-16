#ifndef DBMANAGER_H
#define DBMANAGER_H

// System include
#include <QSqlDatabase>
#include <string>
using namespace std;

// Personnal include
#include "Analyse.h"
#include "HealthPrint.h"
#include "UpdateInterface.h"
#include "Disease.h"


// Constants

// Types

// Class
class DbManager
{
	// Attributes
private:
	QSqlDatabase database;

	// Methods
public:
	// Constructors
	DbManager(const string& path);

	// Destructors
	~DbManager();

	// Others
	bool insertIntoDatabase(const Analyse& analyse);
	bool insertIntoDatabase(const vector<Analyse>& diseases);
	static bool insertAttributes(vector<UpdateInterface::attributeContent*> attributesData);
	static bool insertDiseases(vector<UpdateInterface::diseaseContent*> diseasesData);
	static bool insertDiscriminantAttributes(vector<UpdateInterface::discriminantAttributesContent*> discriminantDiseasesData);
	static bool insertContinuousNormalValues(vector<UpdateInterface::continuousValuesContent*> continuousValuesData);
	static bool insertDiscretNormalValues(vector<UpdateInterface::discretesValuesContent*> discretesValuesData);

	vector<Analyse> getAnalyseResults(string patientName);

	vector<shared_ptr<Attribute>> getDiscriminantAttributesForDisease(int diseaseId);
	vector<Disease> getDiseases();
	shared_ptr<Attribute> getAttributeForId(int attributeId);
	vector<interval> getNormalIntervalsForContinuousAttribute(int attributeId);
	vector<string> getNormalValuesForDiscreteAttribute(int attributeId);
private:
	vector<PotentialDisease> getPotentialDiseaseForAnalyse(int analyseId);
	map<string, double> getAbnormalContinuousAttributesForPotentialDisease(const int diseaseId, const int analyseId);
	map<string, string> getAbnormalDiscreteAttributesForPotentialDisease(const int diseaseId, const int analyseId);

	map<string, double> getContinuousAttributeForHealthPrint(const int healthPrintId);
	map<string, string> getDiscreteAttributeForHealthPrint(const int healthPrintId);

	HealthPrint getHealthprint(const int healthPrintId);


	void wipeData();
};

#endif // DBMANAGER_H
