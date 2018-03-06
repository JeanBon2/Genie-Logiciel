#ifndef DBMANAGER_H
#define DBMANAGER_H

// System include
#include <QSqlDatabase>
#include <string>
using namespace std;

// Personnal include
#include "Analyse.h"
#include "HealthPrint.h"

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
	vector<Analyse> getAnalyseResults(string patientName);

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
