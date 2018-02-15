// System include
#include <iostream>
#include <string>
#include <QSqlQuery>
#include <QVariant>
using namespace std;

// Personnal include
#include "DbManager.h"

// Constants

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
bool DbManager::insertIntoDatabase(const vector<Disease>& diseases)
{
	for (auto&& disease : diseases)
	{
		if (!insertIntoDatabase(disease))
		{
			return false;
		}
	}
	return true;
}


// Private methods
bool DbManager::insertIntoDatabase(const Disease& disease)
{
	QSqlQuery query;
	query.prepare("INSERT INTO Diseases VALUES (:id, :name)");
	query.bindValue(":id", QString::number(disease.getId()));
	query.bindValue(":name", QString::fromStdString(disease.getName()));
	if (!query.exec())
	{
		return false;
	}

	for (auto&& attribute : disease.getDiscriminantAttributes())
	{
		if (!(insertIntoDatabase(attribute) && insertIntoDatabase(disease.getId(), attribute->getId())))
		{
			return false;
		}
	}

	return true;
}


bool DbManager::insertIntoDatabase(const Attribute* attribute)
{
	QSqlQuery query;
	query.prepare("INSERT INTO Attributes VALUES (:id, :name, :discrete)");
	query.bindValue(":id", QString::number(attribute->getId()));
	query.bindValue(":name", QString::fromStdString(attribute->getName()));
	query.bindValue(":discrete", attribute->isDiscrete());
	if (!query.exec())
	{
		return false;
	}

	if (attribute->isDiscrete())
	{
		const DiscreteAttribute* discreteAttribute = static_cast<const DiscreteAttribute*>(attribute);
		return insertIntoDatabase(*discreteAttribute);
	}
	else
	{
		const ContinuousAttribute* continuousAttribute = static_cast<const ContinuousAttribute*>(attribute);
		return insertIntoDatabase(*continuousAttribute);
	}
}
bool DbManager::insertIntoDatabase(const DiscreteAttribute& attribute)
{
	QSqlQuery query;
	query.prepare("INSERT INTO DiscreteNormalValues (attributeId, normalValue, normalValueName) VALUES (:id, :value, :valueName)");
	for (auto&& normalValue : attribute.getNormalValues())
	{
		query.bindValue(":id", QString::number(attribute.getId()));
		query.bindValue(":value", QString::fromStdString(normalValue.first));
		query.bindValue(":valueName", QString::number(normalValue.second));
		if (!query.exec())
		{
			return false;
		}
	}
	return true;
}
bool DbManager::insertIntoDatabase(const ContinuousAttribute& attribute)
{
	QSqlQuery query;
	query.prepare("INSERT INTO ContinuousNormalValues (attributeId, minimumValue, maximumValue) VALUES (:id, :minimum, :maximum)");
	for (auto&& normalInterval : attribute.getNormalIntervals())
	{
		query.bindValue(":id", QString::number(attribute.getId()));
		query.bindValue(":minimum", QString::number(normalInterval.first));
		query.bindValue(":maximum", QString::number(normalInterval.second));
		if (!query.exec())
		{
			return false;
		}
	}
	return true;
}

bool DbManager::insertIntoDatabase(const int diseaseId, const int attributeId)
{
	QSqlQuery query;
	query.prepare("INSERT INTO DiscriminantAttributes (diseaseId, attributeId) VALUES (:diseaseId, :attributeId)");
	query.bindValue(":diseaseId", QString::number(diseaseId));
	query.bindValue(":attributeId", QString::number(attributeId));
	return query.exec();
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
}