// System include
#include <iostream>
#include <string>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QDebug>
using namespace std;

// Personnal include
#include "DbManager.h"
#include "Log.h"

QSqlDatabase DbManager::database = QSqlDatabase::addDatabase("QSQLITE");

// Constructors
DbManager::DbManager(const string& path)
{
#ifdef DEBUG
	cout << "DbManager constructor call" << endl;
#endif // DEBUG
	if (!database.isOpen())
	{
		database.setDatabaseName(QString::fromStdString(path));
	}

	if (!database.open())
	{
		Log::info("Error while opening database.");
		return;
	}
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
	wipeData();
	for (auto&& disease : diseases)
	{
		if (!insertIntoDatabase(disease))
		{
			return false;
		}
	}
	return true;
}
vector<Disease> DbManager::getDiseases()
{
	vector<Disease> diseases;
	QSqlQuery query("SELECT diseaseId, diseaseName FROM Diseases");
	if (query.exec())
	{
		QSqlRecord record = query.record();
		const int indexId = record.indexOf("diseaseId");
		const int indexName = record.indexOf("diseaseName");
		while (query.next())
		{
			const int diseaseId = query.value(indexId).toInt();
			const string diseaseName = query.value(indexName).toString().toUtf8().constData();
			diseases.emplace_back(diseaseId, diseaseName, getDiscriminantAttributesForDisease(diseaseId));
		}
	}
	return diseases;
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
bool DbManager::insertIntoDatabase(const shared_ptr<Attribute> attribute)
{
	QSqlQuery query;
	query.prepare("INSERT INTO Attributes VALUES (:id, :name, :discrete)");
	query.bindValue(":id", QString::number(attribute->getId()));
	query.bindValue(":name", QString::fromStdString(attribute->getName()));
	query.bindValue(":discrete", attribute->isDiscrete());
	if (!query.exec())
	{
		if (getAttributeForId(attribute->getId()) != nullptr)	// If the attribute is already in the database, it's all right.
		{
			return true;
		}
		return false;
	}

	if (attribute->isDiscrete())
	{
		shared_ptr<DiscreteAttribute> discreteAttribute = dynamic_pointer_cast<DiscreteAttribute>(attribute);
		return insertIntoDatabase(*discreteAttribute);
	}
	else
	{
		shared_ptr<ContinuousAttribute> continuousAttribute = dynamic_pointer_cast<ContinuousAttribute>(attribute);
		return insertIntoDatabase(*continuousAttribute);
	}
}
bool DbManager::insertIntoDatabase(const DiscreteAttribute& attribute)
{
	QSqlQuery query;
	query.prepare("INSERT INTO DiscreteNormalValues (attributeId, normalValue) VALUES (:id, :value)");
	for (auto&& normalValue : attribute.getNormalValues())
	{
		query.bindValue(":id", QString::number(attribute.getId()));
		query.bindValue(":value", QString::fromStdString(normalValue));
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

vector<shared_ptr<Attribute>> DbManager::getDiscriminantAttributesForDisease(int diseaseId)
{
	vector<shared_ptr<Attribute>> attributes;

	QSqlQuery query;
	query.prepare("SELECT discriminantAttributeId, attributeId FROM DiscriminantAttributes WHERE diseaseId = :diseaseId ORDER BY discriminantAttributeId ASC");
	query.bindValue(":diseaseId", diseaseId);
	if (query.exec())
	{
		QSqlRecord record = query.record();
		const int indexAttributeId = record.indexOf("attributeId");
		while (query.next())
		{
			int attributeId = query.value(indexAttributeId).toInt();

			shared_ptr<Attribute> attribute = getAttributeForId(attributeId);
			if (attribute != nullptr)
			{
				attributes.emplace_back(attribute);
			}
		}
	}
	query.finish();
	return attributes;
}
shared_ptr<Attribute> DbManager::getAttributeForId(int attributeId)
{
	QSqlQuery query;
	query.prepare("SELECT name, discrete FROM Attributes where attributeId = :attributeId");
	query.bindValue(":attributeId", attributeId);
	if (query.exec())
	{
		QSqlRecord record = query.record();
		const int indexName = query.record().indexOf("name");
		const int indexDiscrete = query.record().indexOf("discrete");
		if (query.next())
		{
			const string name = query.value(indexName).toString().toUtf8().constData();
			const bool discrete = query.value(indexDiscrete).toBool();
			if (discrete)
			{
				return std::static_pointer_cast<Attribute>(
					std::make_shared<DiscreteAttribute>(attributeId, name, getNormalValuesForDiscreteAttribute(attributeId)));
			}
			else
			{
				return std::static_pointer_cast<Attribute>(
					std::make_shared<ContinuousAttribute>(attributeId, name, getNormalIntervalsForContinuousAttribute(attributeId)));
			}
		}
	}

	return nullptr;
}
vector<interval> DbManager::getNormalIntervalsForContinuousAttribute(int attributeId)
{
	vector<interval> normalIntervals;

	QSqlQuery query;
	query.prepare("SELECT minimumValue, maximumValue FROM ContinuousNormalValues WHERE attributeId = :attributeId");
	query.bindValue(":attributeId", attributeId);
	if (query.exec())
	{
		QSqlRecord record = query.record();
		const int indexMinimum = record.indexOf("minimumValue");
		const int indexMaximum = record.indexOf("maximumValue");
		while (query.next())
		{
			double minimum = query.value(indexMinimum).toDouble();
			double maximum = query.value(indexMaximum).toDouble();
			normalIntervals.emplace_back(minimum, maximum);
		}
	}
	return normalIntervals;
}
vector<string> DbManager::getNormalValuesForDiscreteAttribute(int attributeId)
{
	vector<string> normalValues;

	QSqlQuery query;
	query.prepare("SELECT normalValue FROM DiscreteNormalValues WHERE attributeId = :attributeId");
	query.bindValue(":attributeId", attributeId);
	if (query.exec())
	{
		QSqlRecord record = query.record();
		const int indexNormalValue = record.indexOf("normalValue");
		while (query.next())
		{
			string normalValue = query.value(indexNormalValue).toString().toUtf8().constData();
			normalValues.emplace_back(normalValue);
		}
	}
	return normalValues;
}

vector<shared_ptr<Attribute>> DbManager::getAttributes()
{
	vector<shared_ptr<Attribute>> attributes;

	QSqlQuery query;
	query.prepare("SELECT attributeId, name, discrete FROM Attributes;");
	if (query.exec())
	{
		QSqlRecord record = query.record();
		const int indexAttributeId = query.record().indexOf("attributeId");
		const int indexName = query.record().indexOf("name");
		const int indexDiscrete = query.record().indexOf("discrete");
		while (query.next())
		{
			const int attributeId = query.value(indexAttributeId).toInt();
			const string name = query.value(indexName).toString().toUtf8().constData();
			const bool discrete = query.value(indexDiscrete).toBool();
			if (discrete)
			{
				attributes.emplace_back(std::static_pointer_cast<Attribute>(
					std::make_shared<DiscreteAttribute>(attributeId, name, getNormalValuesForDiscreteAttribute(attributeId))));
			}
			else
			{
				attributes.emplace_back(std::static_pointer_cast<Attribute>(
					std::make_shared<ContinuousAttribute>(attributeId, name, getNormalIntervalsForContinuousAttribute(attributeId))));
			}
		}
	}
	return attributes;
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
