// System include
#include <iostream>
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
	for (auto&& analyse : analyses)
	{
		if (!insertIntoDatabase(analyse))
		{
			return false;
		}
	}
	return true;
}
vector<Analyse> DbManager::getAnalyseResults()
{
	vector<Analyse> analyses;
	QSqlQuery query("SELECT diseaseId, diseaseName FROM Diseases");
	if (query.exec())
	{
		QSqlRecord record = query.record();
		const int indexId = record.indexOf("diseaseId");
		const int indexName = record.indexOf("diseaseName");
		while (query.next())
		{
			const int diseaseId = query.value(indexId).toInt();
			const string diseaseName = query.value(indexName).toString().toStdString();
			//diseases.emplace_back(diseaseId, diseaseName, getDiscriminantAttributesForDisease(diseaseId));
		}
	}
	return analyses;
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
