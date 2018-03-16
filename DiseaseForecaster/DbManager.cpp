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
#include "UpdateInterface.h"

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
bool DbManager::insertIntoDatabase(vector<Analyse>& analyses)
{
    bool insertSuccess= true;
    for (auto&& analyse : analyses)
    {
        if (!insertAnalyse(analyse))
        {
            insertSuccess = false;
        }
    }
    return insertSuccess;
}
vector<Analyse> DbManager::getAnalyseResults(const string patientName)
{
    const QString sqlQuery = "SELECT a.analyseId,\
            h.patientName, h.doctorName, h.printDate,\
            p.matchingRate,\
            d.diseaseName,\
            hpav.attributeValue, hpav.valueName,\
            att.name, att.discrete\
            FROM Analyses a INNER JOIN HealthPrints h ON a.healthPrintId = h.healthPrintId\
            INNER JOIN PotentialDiseases p ON a.analyseId = p.analyseId\
            INNER JOIN Diseases d ON p.diseaseId = d.diseaseId\
            INNER JOIN AbnormalAttributes abatt ON p.potentialDiseaseId = abatt.potentialDiseaseId\
            INNER JOIN HealthPrintAttributeValues hpav ON abatt.healthPrintAttributeValuesId = hpav.healthPrintAttributeValuesId\
            INNER JOIN Attributes att ON hpav.attributeId = att.attributeId\
            WHERE h.patientName = :patientName\
            ORDER BY a.analyseId, p.potentialDiseaseId, h.printDate;";

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
            const unsigned int healthPrintIdValue = query.value(indexHealthPrintId).toInt();
            const string patientNameValue = query.value(indexPatientName).toString().toStdString();
            const string doctorNameValue = query.value(indexDoctorName).toString().toStdString();
            const string printDateValue = query.value(indexPrintDate).toString().toStdString();
            const unsigned int sensorIdValue = query.value(indexSensorId).toInt();

            HealthPrint healthPrint(healthPrintIdValue, patientNameValue, doctorNameValue, printDateValue, sensorIdValue);
            Analyse analyse(analyseIdValue, healthPrint, getPotentialDiseaseForAnalyse(analyseIdValue));

            analysesLists.emplace_back(analyse);
        }
    }
    return analysesLists;
}
bool DbManager::insertAttributes(vector<UpdateInterface::attributeContent*> attributesData)
{

    for (auto && attr : attributesData)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO Attributes (AttributeId, name, discrete) VALUES (:id, :name, :discrete)");
        query.bindValue(":id", QString::number(attr->id));
        query.bindValue(":name", QString::fromStdString(attr->name));
        query.bindValue(":discrete", QString::number(attr->discrete));
        if (!query.exec())
        {
            return false;
        }
    }
    return true;
}

bool DbManager::insertDiseases(vector<UpdateInterface::diseaseContent*> diseasesData)
{
    for (auto && disease : diseasesData)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO Diseases (diseaseId, diseaseName) VALUES (:id, :name)");
        query.bindValue(":id", QString::number(disease->id));
        query.bindValue(":name", QString::fromStdString(disease->name));
        if (!query.exec())
        {
            return false;
        }
    }
    return true;
}
bool DbManager::insertDiscriminantAttributes(vector<UpdateInterface::discriminantAttributesContent*> discriminantDiseasesData)
{
    for (auto && discAttr : discriminantDiseasesData)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO DiscriminantAttributes (diseaseId, attributeId) VALUES (:idDisease, :idAttr)");
        query.bindValue(":idDisease", QString::number(discAttr->diseaseId));
        query.bindValue(":idAttr", QString::number(discAttr->attributeId));
        if (!query.exec())
        {
            return false;
        }
    }
    return true;
}
bool DbManager::insertContinuousNormalValues(vector<UpdateInterface::continuousValuesContent*> continuousValuesData) {

    for (auto && contValues : continuousValuesData)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO ContinuousNormalValues (attributeId, minimumValue, maximumValue) VALUES (:attId, :minVal, :maxVal)");
        query.bindValue(":attId", QString::number(contValues->attributeId));
        query.bindValue(":minVal", QString::number(contValues->minimumValue));
        query.bindValue(":maxVal", QString::number(contValues->maximumValue));
        if (!query.exec())
        {
            return false;
        }
    }
    return true;
}
bool DbManager::insertDiscretNormalValues(vector<UpdateInterface::discretesValuesContent*> discretesValuesData)
{

    for (auto && discValues : discretesValuesData)
    {
        QSqlQuery query;
        query.prepare("INSERT INTO DiscreteNormalValues (attributeId, normalValue) VALUES (:attId, :normVal)");
        query.bindValue(":attId", QString::number(discValues->attributeId));
        query.bindValue(":normVal", QString::fromStdString(discValues->normalValue));
        if (!query.exec())
        {
            return false;
        }
    }
    return true;
}
bool DbManager::insertAnalyse(Analyse& analyse)
{
    insertHealthPrint(analyse.getHealthPrint());
    QSqlQuery query;
    query.prepare("INSERT INTO Analyses VALUES (:healthprintId)");
    query.bindValue(":healthprintId", analyse.getHealthPrint().getId());
    analyse.setId(getLastIndex("Analyses"));
    if (!query.exec())
    {
        return false;
    }
    for(auto potentialdisease : analyse.getDiseases())
    {
        //insertPotentialDisease(potentialdisease);
    }
    return true;
}

// Private methods
vector<PotentialDisease> DbManager::getPotentialDiseaseForAnalyse(const int analyseId)
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
        const unsigned int indexDiseaseId = record.indexOf("diseaseId");

        while (query.next())
        {
            const unsigned int potentialDiseaseIdValue = query.value(indexPotentialDiseaseId).toInt();
            const double matchingRateValue = query.value(indexMatchingRate).toDouble();
            const string diseaseNameValue = query.value(indexDiseaseName).toString().toStdString();
            const unsigned int diseaseIdValue = query.value(indexDiseaseId).toInt();

            potentialDiseases.push_back(
                        PotentialDisease(potentialDiseaseIdValue, diseaseNameValue, matchingRateValue,
                                         getAbnormalContinuousAttributesForPotentialDisease(diseaseIdValue, analyseId),
                                         getAbnormalDiscreteAttributesForPotentialDisease(diseaseIdValue, analyseId)));
        }
    }
    return potentialDiseases;
}

map<string, double> DbManager::getAbnormalContinuousAttributesForPotentialDisease(const int diseaseId, const int analyseId)
{
    map<string,double> abnormalContinuousAttributes;
    const QString sqlQuery = "SELECT name, attributeValue \
            FROM HealthPrintAttributeValues hpav INNER JOIN Attributes a ON a.attributeid = hpav.attributeid \
            INNER JOIN DiscriminantAttributes da ON da.attributeId = hpav.attributeId \
            INNER JOIN Diseases d ON d.diseaseId = da.diseaseId\
            INNER JOIN PotentialDiseases pd ON pd.diseaseId = da.diseaseId \
            INNER JOIN AbnormalAttributes aa ON aa.healthPrintAttributeValuesId = hpav.healthPrintAttributeValuesId \
            WHERE diseaseId = :diseaseId AND discrete = 0 AND analyseId = :analyseId \
            ORDER BY :diseaseId";

            QSqlQuery query;
    query.prepare(sqlQuery);
    query.bindValue(":diseaseId", diseaseId);
    query.bindValue(":analyseId", analyseId);
    if (query.exec())
    {
        QSqlRecord record = query.record();

        const unsigned int indexAttributeName = record.indexOf("name");
        const unsigned int indexAttributeValue = record.indexOf("attributeValue");

        while (query.next())
        {
            const string AttributeNameValue = query.value(indexAttributeName).toString().toStdString();
            const double AttributeValueValue = query.value(indexAttributeValue).toDouble();
            abnormalContinuousAttributes.emplace(AttributeNameValue, AttributeValueValue);
        }
    }
    return abnormalContinuousAttributes;
}
map<string, string> DbManager::getAbnormalDiscreteAttributesForPotentialDisease(const int diseaseId, const int analyseId)
{
    map<string, string> abnormalDiscreteAttributes;
    const QString sqlQuery = "SELECT name, valueName \
            FROM HealthPrintAttributeValues hpav INNER JOIN Attributes a ON a.attributeid = hpav.attributeid \
            INNER JOIN DiscriminantAttributes da ON da.attributeId = hpav.attributeId \
            INNER JOIN Diseases d ON d.diseaseId = da.diseaseId\
            INNER JOIN PotentialDiseases pd ON pd.diseaseId = da.diseaseId \
            INNER JOIN AbnormalAttributes aa ON aa.healthPrintAttributeValuesId = hpav.healthPrintAttributeValuesId \
            WHERE diseaseId = :diseaseId AND discrete <> 0 AND analyseId = :analyseId \
            ORDER BY :diseaseId";

            QSqlQuery query;
    query.prepare(sqlQuery);
    query.bindValue(":diseaseId", diseaseId);
    query.bindValue(":analyseId", analyseId);
    if (query.exec())
    {
        QSqlRecord record = query.record();

        const unsigned int indexAttributeName = record.indexOf("name");
        const unsigned int indexAttributeValueName = record.indexOf("valueName");

        while (query.next())
        {
            const string AttributeNameValue = query.value(indexAttributeName).toString().toStdString();
            const string AttributeValueValue = query.value(indexAttributeValueName).toString().toStdString();

            abnormalDiscreteAttributes.emplace(AttributeNameValue, AttributeValueValue);
        }
    }
    return abnormalDiscreteAttributes;
}

map<string, double> DbManager::getContinuousAttributeForHealthPrint(const int healthPrintId)
{
    map<string, double> continuousAttributes;
    const QString sqlQuery = "SELECT name, attributeValue \
            FROM HealthPrints hp INNER JOIN HealthPrintAttributesValues hpav ON hpav.attributeid = hp.attributeId \
            INNER JOIN Attributes a ON a.attributeId = hpav.attributeId \
            WHERE healthPrintId = :HealthprintId AND discrete = 0";

            QSqlQuery query;
    query.prepare(sqlQuery);
    query.bindValue(":HealthprintId", healthPrintId);
    if (query.exec())
    {
        QSqlRecord record = query.record();

        const unsigned int indexAttributeName = record.indexOf("name");
        const unsigned int indexAttributeValue = record.indexOf("attributeValue");

        while (query.next())
        {
            const string AttributeNameValue = query.value(indexAttributeName).toString().toStdString();
            const double AttributeValueValue = query.value(indexAttributeValue).toDouble();
            continuousAttributes.emplace(AttributeNameValue, AttributeValueValue);
        }
    }
    return continuousAttributes;
}
map<string, string> DbManager::getDiscreteAttributeForHealthPrint(const int healthPrintId)
{
    map<string, string> discreteAttributes;
    const QString sqlQuery = "SELECT name, attributeValue \
            FROM HealthPrints hp INNER JOIN HealthPrintAttributesValues hpav ON hpav.attributeid = hp.attributeId \
            INNER JOIN Attributes a ON a.attributeId = hpav.attributeId \
            WHERE healthPrintId = :HealthprintId AND discrete <> 0";

            QSqlQuery query;
    query.prepare(sqlQuery);
    query.bindValue(":HealthprintId", healthPrintId);
    if (query.exec())
    {
        QSqlRecord record = query.record();

        const unsigned int indexAttributeName = record.indexOf("name");
        const unsigned int indexAttributeValue = record.indexOf("attributeValue");

        while (query.next())
        {
            const string AttributeNameValue = query.value(indexAttributeName).toString().toStdString();
            const string AttributeValueValue = query.value(indexAttributeValue).toString().toStdString();
            discreteAttributes.emplace(AttributeNameValue, AttributeValueValue);
        }
    }
    return discreteAttributes;
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
HealthPrint DbManager::getHealthprint(const int healthPrintId)
{
    const QString sqlQuery = "SELECT patientName, doctorName, printDate, sensorId \
            FROM HealthPrints WHERE HealthprintId = :HealthprintId";

            QSqlQuery query;
    query.prepare(sqlQuery);
    query.bindValue(":HealthprintId", healthPrintId);
    if (query.exec())
    {
        QSqlRecord record = query.record();

        const unsigned int indexPatientName = record.indexOf("patientName");
        const unsigned int indexDoctorName = record.indexOf("doctorName");
        const unsigned int indexPrintDate = record.indexOf("printDate");
        const unsigned int indexSensorId = record.indexOf("sensorId");

        if (query.next())
        {
            const string patientNameValue = query.value(indexPatientName).toString().toStdString();
            const string doctorNameValue = query.value(indexDoctorName).toString().toStdString();
            const string printDateValue = query.value(indexPrintDate).toString().toStdString();
            const int sensorIdValue = query.value(indexSensorId).toInt();

            HealthPrint foundHealthprint = HealthPrint(healthPrintId, patientNameValue, doctorNameValue, printDateValue, sensorIdValue, getContinuousAttributeForHealthPrint(healthPrintId), getDiscreteAttributeForHealthPrint(healthPrintId));
            return foundHealthprint;
        }
    }
    return HealthPrint(0, "", "", "", 0);
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
bool DbManager::insertHealthPrint(HealthPrint& healthprint)
{
    QSqlQuery query;
    query.prepare("INSERT INTO HealthPrints (patientName, doctorName, printDate, sensorId) VALUES (:patientName, :doctorName, :printDate, :sensorId )");
    query.bindValue(":patientName", QString::fromStdString(healthprint.getPatientName()));
    query.bindValue(":doctorName", QString::fromStdString(healthprint.getDoctorName()));
    query.bindValue(":printDate", healthprint.getPrintDate());
    query.bindValue(":sensorId", healthprint.getSensorId());
    if (!query.exec())
    {
        return false;
    }
    healthprint.setId(getLastIndex("HealthPrint"));
    for(auto&& continuousAttributesValues : healthprint.getContinuousAttributesValues())
    {
        int attributeId;
        query.prepare("SELECT attributeId FROM Attributes WHERE name = :name");
        query.bindValue(":name", QString::fromStdString(continuousAttributesValues.first));
        if (query.exec() && query.next())
        {
            QSqlRecord record = query.record();
            const int indexAttributeId = record.indexOf("attributeId");
            attributeId = query.value(indexAttributeId).toInt();
        }
        else
        {
            return false;
        }

        query.prepare("INSERT INTO HealthPrintAttributeValues (attributeValue, healthPrintId, attributeId) VALUES (:attributeValue, :healthPrintId, :attributeId)");
        query.bindValue(":attributeValue", continuousAttributesValues.second);
        query.bindValue(":healthPrintId", healthprint.getId());
        query.bindValue(":attributeId", attributeId);
    }
    for(auto&& discreteAttributesValues : healthprint.getDiscreteAttributesValues())
    {
        int attributeId;
        query.prepare("SELECT attributeId FROM Attributes WHERE name = :name");
        query.bindValue(":name", QString::fromStdString(discreteAttributesValues.first));
        if (query.exec() && query.next())
        {
            QSqlRecord record = query.record();
            const int indexAttributeId = record.indexOf("attributeId");
            attributeId = query.value(indexAttributeId).toInt();
        }
        else
        {
            return false;
        }

        query.prepare("INSERT INTO HealthPrintAttributeValues (valueName, healthPrintId, attributeId) VALUES (:valueName, :healthPrintId, :attributeId)");
        query.bindValue(":valueName", QString::fromStdString(discreteAttributesValues.second));
        query.bindValue(":healthPrintId", healthprint.getId());
        query.bindValue(":attributeId", attributeId);
    }

    return true;
}
bool DbManager::insertPotentialDisease(PotentialDisease potentialdisease, int analyseId, HealthPrint healthPrint)
{
    QSqlQuery query;
    int diseaseId;
    query.prepare("SELECT diseaseId FROM Disease WHERE diseaseName = :name");
    query.bindValue(":name", QString::fromStdString(potentialdisease.getName()));
    if (query.exec() && query.next())
    {
        QSqlRecord record = query.record();
        const int indexDiseaseId = record.indexOf("diseaseId");
        diseaseId = query.value(indexDiseaseId).toInt();
    }
    else
    {
        return false;
    }
    query.prepare("INSERT INTO PotentialDiseases (matchingRate, analyseId, diseaseId) VALUES (:matchingRate, :analyseId, :diseaseId)");
    query.bindValue(":matchingRate", potentialdisease.getMatchingRate());
    query.bindValue(":analyseId", analyseId);
    query.bindValue("diseaseId",diseaseId);
    potentialdisease.setId(getLastIndex("PotentialDiseases"));

    if (!query.exec())
    {
        return false;
    }
    potentialdisease.setId(getLastIndex("PotentialDisease"));
    for(auto&& continuousAttributesValues : potentialdisease.getContinuousAttributesValues())
    {
        int healthPrintAttributeValuesId;
        query.prepare("SELECT healthPrintAttributeValuesId FROM HealthPrintAttributeValuesId WHERE healthPrintId = :healthPrintId AND attributeValue= :attributeValue");
        query.bindValue(":healthPrintId", healthPrint.getId());
        query.bindValue(":attributeValue", healthPrint.getContinuousAttributesValues().operator [](continuousAttributesValues.first));
        if (query.exec() && query.next())
        {
            QSqlRecord record = query.record();
            const int indexAttributeId = record.indexOf("healthPrintId");
            healthPrintAttributeValuesId = query.value(indexAttributeId).toInt();
        }
        else
        {
            return false;
        }
        query.prepare("INSERT INTO AbnormaAttributes (healthPrintAttributeValuesId, potentialDiseaseId) VALUES (:healthPrintAttributeValuesId, :potentialDiseaseId)");
        query.bindValue(":healthPrintAttributeValuesId", healthPrintAttributeValuesId);
        query.bindValue(":potentialDiseaseId", potentialdisease.getId());
        if (!query.exec())
        {
            return false;
        }
    }
    for(auto&& discreteAttributesValues : potentialdisease.getDiscreteAttributesValues())
    {
        int healthPrintAttributeValuesId;
        query.prepare("SELECT healthPrintAttributeValuesId FROM HealthPrintAttributeValuesId WHERE healthPrintId = :healthPrintId AND ValueName= :ValueName");
        query.bindValue(":healthPrintId", healthPrint.getId());
        query.bindValue(":ValueName", QString::fromStdString(healthPrint.getDiscreteAttributesValues().operator [](discreteAttributesValues.first)));
        if (query.exec() && query.next())
        {
            QSqlRecord record = query.record();
            const int indexAttributeId = record.indexOf("healthPrintId");
            healthPrintAttributeValuesId = query.value(indexAttributeId).toInt();
        }
        else
        {
            return false;
        }
        query.prepare("INSERT INTO AbnormaAttributes (healthPrintAttributeValuesId, potentialDiseaseId) VALUES (:healthPrintAttributeValuesId, :potentialDiseaseId)");
        query.bindValue(":healthPrintAttributeValuesId", healthPrintAttributeValuesId);
        query.bindValue(":potentialDiseaseId", potentialdisease.getId());
        if (!query.exec())
        {
            return false;
        }
    }
    return true;
}
int DbManager::getLastIndex(string tablename)
{
    QSqlQuery query;
    query.prepare("SELECT Seq WHERE name = :tablename");
    query.bindValue(":tableName", QString::fromStdString(tablename));
    if (query.exec() && query.next())
    {
        QSqlRecord record = query.record();
        const int indexSeqId = record.indexOf("Seq");
        return query.value(indexSeqId).toInt();
    }
    return 0;
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
