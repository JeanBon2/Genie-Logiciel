// System include
#include <iostream>
#include <map>
#include <string>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
using namespace std;

// Personnal include
#include "DbManager.h"

// Constructors
DbManager::DbManager(const string& path)
{
#ifdef DEBUG
	cout << "DbManager constructor call" << endl;
#endif // DEBUG
	database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName(QString::fromStdString(path));

	if (!database.open())
	{
		// Log
		return;
	}
	wipeData();
}

// Destructor
DbManager::~DbManager()
{
#ifdef DEBUG
	cout << "DbManager destructor call" << endl;
#endif // DEBUG
	database.close();
}

// Public methods
bool DbManager::insertIntoDatabase(const vector<Analyse>& analyses)
{
	bool insertSuccess= true;
	for (auto&& analyse : analyses)
	{
		if (!insertIntoDatabase(analyse))
		{
			insertSuccess = false;
		}
	}
	return insertSuccess;
}
vector<Analyse> DbManager::getAnalyseResults(const string patientName)
{
	//const QString sqlQuery = "SELECT a.analyseId,\
	//	h.patientName, h.doctorName, h.printDate,\
	//	p.matchingRate,\
	//	d.diseaseName,\
	//	hpav.attributeValue, hpav.valueName,\
	//	att.name, att.discrete\
	//	FROM Analyses a INNER JOIN HealthPrints h ON a.healthPrintId = h.healthPrintId\
	//	INNER JOIN PotentialDiseases p ON a.analyseId = p.analyseId\
	//	INNER JOIN Diseases d ON p.diseaseId = d.diseaseId\
	//	INNER JOIN AbnormalAttributes abatt ON p.potentialDiseaseId = abatt.potentialDiseaseId\
	//	INNER JOIN HealthPrintAttributeValues hpav ON abatt.healthPrintAttributeValuesId = hpav.healthPrintAttributeValuesId\
	//	INNER JOIN Attributes att ON hpav.attributeId = att.attributeId\
	//	WHERE h.patientName = :patientName\
	//	ORDER BY a.analyseId, p.potentialDiseaseId, h.printDate;";

	// Without patientName, for tests
	const QString sqlQuery = "SELECT a.analyseId,\
		h.healthPrintId, h.patientName, h.doctorName, h.printDate,h.sensorId\
		FROM Analyses a INNER JOIN HealthPrints h ON a.healthPrintId = h.healthPrintId\
		ORDER BY a.analyseId, h.printDate;";
	vector<Analyse> analysesLists;
	map<string, double> continuousAttributesValues;
	map<string, string> discreteAttributesValues;

	QSqlQuery query;

	query.prepare(sqlQuery);
	query.bindValue(":patientName", QString::fromStdString(patientName));
	if (query.exec())
	{
		QSqlRecord record = query.record();
		//empreintes
		const unsigned int indexAnalyseId = record.indexOf("analyseId");
		const unsigned int indexHealthPrintId = record.indexOf("healthPrintId");
		const unsigned int indexPatientName = record.indexOf("patientName");
		const unsigned int indexDoctorName = record.indexOf("doctorName");
		const unsigned int indexPrintDate = record.indexOf("printDate");
		const unsigned int indexSensorId = record.indexOf("sensorId");
		
		while (query.next())
		{

			const unsigned int analyseIdValue = query.value(indexAnalyseId).toInt();
			const unsigned int healthPrintIdValue = query.value(indexAnalyseId).toInt();
			const string patientNameValue = query.value(indexPatientName).toString().toStdString();
			const string doctorNameValue = query.value(indexDoctorName).toString().toStdString();
			const string printDateValue = query.value(indexPrintDate).toString().toStdString();
			const unsigned int sensorIdValue = query.value(indexSensorId).toInt();

			const HealthPrint healthPrint(healthPrintIdValue, patientNameValue, doctorNameValue, printDateValue, sensorIdValue);
			Analyse analyse(analyseIdValue, healthPrint, getPotentialDiseaseForAnalyse(analyseIdValue));

			analysesLists.emplace_back(analyse);
		}
	}
	return analysesLists;
}

// Private methods
bool DbManager::insertIntoDatabase(const Analyse& analyse)
{
	QSqlQuery query;
	query.prepare("INSERT INTO Diseases VALUES (:id, :name)");
	//query.bindValue(":id", QString::number(analyse.getId()));
	//query.bindValue(":name", QString::fromStdString(disease.getName()));
	if (!query.exec())
	{
		return false;
	}
	return true;
}

vector<PotentialDisease> DbManager::getPotentialDiseaseForAnalyse(int analyseId)
{
	vector<PotentialDisease> potentialDiseases;
	const QString sqlQuery = "SELECT potentialDiseaseId, diseaseId, matchingRate, diseaseName \
	FROM PotentialDiseases p INNER JOIN Analyses a ON p.analyseId = a.analyseId \
	WHERE analyseId = :analyseId";
	QSqlQuery query;

	query.prepare(sqlQuery);
	query.bindValue(":analyseId", analyseId);
	if (query.exec())
	{
		QSqlRecord record = query.record();
		//empreintes
		const unsigned int indexPotentialDiseaseId = record.indexOf("potentialDiseaseId");
		const unsigned int indexMatchingRate = record.indexOf("matchingRate");
		const unsigned int indexDiseaseName = record.indexOf("diseaseName");

		while (query.next())
		{

			const unsigned int potentialDiseaseIdValue = query.value(indexPotentialDiseaseId).toInt();
			const double matchingRateValue = query.value(indexMatchingRate).toDouble();
			const string diseaseNameValue = query.value(indexDiseaseName).toString().toStdString();

			/* TODO : r�cup�rer les attributs (dans AbnormalAttributes et HealthPrintAttributeValues) et les ins�rer en param�tres dans emplace_back
			 * N�cessite d'utiliser `potentialDiseaseId` avec une m�thode du style `getAbnormalAttributesForPotentialDisease(int potentialDiseaseId)`
			*/

			//potentialDiseases.emplace_back(potentialDiseaseIdValue, diseaseNameValue, matchingRateValue);
		}
	}
	return potentialDiseases;
}

void DbManager::wipeData()
{
	QSqlQuery query;
	query.prepare("DELETE FROM DiscriminantAttributes");
	query.exec();
	query.prepare("DELETE FROM ContinuousNormalValues");
	query.exec();
	query.prepare("DELETE FROM DiscreteNormalValues");
	query.exec();
	query.prepare("DELETE FROM Attributes");
	query.exec();
	query.prepare("DELETE FROM Diseases");
	query.exec();
	query.prepare("DELETE FROM sqlite_sequence");
	query.exec();
}
