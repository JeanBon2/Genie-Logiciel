// System include
#include <algorithm>
#include <utility>
#include <memory>
using namespace std;

// Personnal include
#include "ModelImporter.h"
#include "CsvParser.h"
#include "ContinuousAttribute.h"
#include "Disease.h"
#include "DbManager.h"
#include "Log.h"

// Constants

// Constructors
ModelImporter::ModelImporter(string pathToDescriptionFile, string pathToValuesFile)
	: pathToDescriptionFile(std::move(pathToDescriptionFile)), pathToValuesFile(std::move(pathToValuesFile))
{
#ifdef DEBUG
	cout << "ModelImporter constructor call" << endl;
#endif // DEBUG
}

// Destructor
ModelImporter::~ModelImporter()
{
#ifdef DEBUG
	cout << "ModelImporter destructor call" << endl;
#endif // DEBUG
}

// Public methods
bool ModelImporter::importModel()
{
	if (!importAttributeNames())
	{
		Log::info("Attributes haven't been imported.");
		return false;
	}
	if (!importAttributeValues())
	{
		Log::info("Attributes values haven't been imported.");
		return false;
	}
	return true;
}

// Private methods
bool ModelImporter::importAttributeNames()
{
	QFile descriptionFile(QString::fromStdString(pathToDescriptionFile));
	vector<vector<string>> lines = CsvParser::staticParse(descriptionFile);
	if (lines.empty())
	{
		QString message("Empty file : ");
		message += QString::fromStdString(pathToDescriptionFile);
		Log::info(message.toStdString());
		return false;
	}
	vector<string>& headers = lines[0];
	string attributeNameHeader = headers[0];
	string attributeTypeHeader = headers[1];
	lines.erase(lines.begin());
	if (headers.size() != 2)
	{
		Log::info("Error while reading headers.");
		return false;
	}

	std::transform(attributeNameHeader.begin(), attributeNameHeader.end(), attributeNameHeader.begin(), ::tolower);
	std::transform(attributeTypeHeader.begin(), attributeTypeHeader.end(), attributeTypeHeader.begin(), ::tolower);
	if (attributeNameHeader != "attributename" || attributeTypeHeader != "attributetype")
	{
		Log::info("Error while reading headers.");
		return false;
	}
	
	unsigned int i = 0;
	for (auto&& line : lines)
	{
		++i;
		if (line.size() != 2)
		{
			QString message("Line ");
			message += QString::number(i) + QString::fromStdString(" is malformed.");
			Log::info(message.toStdString());
			return false;
		}

		const string& attributeName = line[0];
		const string& attributeType = line[1];

		if (attributeType == "String" || attributeType == "string")
		{
			// Attribut discret
			discreteAttributes.emplace(attributeName);
		}
		else
		{
			// Attribut continu
			continuousAttributes.emplace(attributeName);
		}
	}


	return true;
}
bool ModelImporter::importAttributeValues()
{
	/* Format verification */
	QFile valueFile(QString::fromStdString(pathToValuesFile));
	vector<vector<string>> lines = CsvParser::staticParse(valueFile);
	if (lines.empty())
	{
		QString message("Empty file : ");
		message += QString::fromStdString(pathToValuesFile);
		Log::info(message.toStdString());
		return false;
	}

	vector<string> headers = lines[0];
	lines.erase(lines.begin());
	unsigned int headersSize = 0;
	bool diseaseFound = false;
	for (auto&& header : headers)
	{
		if (header == "Disease" || header == "disease"
			|| header == "Desease" || header == "desease")
		{
			diseaseFound = true;
			break;
		}
		if (continuousAttributes.find(header) == continuousAttributes.end()
			&& discreteAttributes.find(header) == discreteAttributes.end())
		{
			QString message("Attribute ");
			message += QString::fromStdString(header) + QString::fromStdString(" is not defined in ") + QString::fromStdString(pathToDescriptionFile);
			Log::info(message.toStdString());
			return false;
		}
		++headersSize;
	}
	if (!diseaseFound)
	{
		Log::info("Error while reading headers : 'Disease' not found.");
		return false;
	}
	if (headersSize != continuousAttributes.size() + discreteAttributes.size())
	{
		Log::info("Error while reading headers : attribute number mismatches.");
		return false;
	}

	/* Real algorithm */
	map<string, vector<double>> healthyContinuousAttributes;
	map<string, vector<string>> healthyDiscreteAttributes;

	map<string, map<string, vector<double>>> continuousAttributesForDisease;
	map<string, map<string, vector<string>>> discreteAttributesForDisease;
	map<string, map<string, unsigned int>> numberOfPersonWithValueOfDiscreteAttribute;

	for (auto&& continuousAttribute : continuousAttributes)
	{
		healthyContinuousAttributes.emplace(continuousAttribute, vector<double>());
	}
	for (auto&& discreteAttribute : discreteAttributes)
	{
		healthyDiscreteAttributes.emplace(discreteAttribute, vector<string>());
	}

	for (auto&& line : lines)
	{
		string disease = line[headersSize];
		if (disease.empty())
		{
			// Healthy patient
			for (unsigned int i = 0; i < headersSize; ++i)
			{
				auto&& attribute = healthyContinuousAttributes.find(headers[i]);
				if (attribute != healthyContinuousAttributes.end())
				{
					auto&& data = attribute->second;
					try
					{
						double value = stod(line[i]);
						data.emplace_back(value);
					}
					catch (invalid_argument)
					{
						QString message("Value ");
						message += QString::fromStdString(line[i]) + QString(" is not a number.");
						Log::info(message.toStdString());
						return false;
					}
				}
				else
				{
					auto&& discreteAttribute = healthyDiscreteAttributes.find(headers[i]);
					if (discreteAttribute == healthyDiscreteAttributes.end())
					{
						QString message("No header found for ");
						message += QString::fromStdString(headers[i]);
						Log::info(message.toStdString());
						return false;
					}
					auto&& data = discreteAttribute->second;
					data.emplace_back(line[i]);

					map<string, unsigned int> numberOfPersonsWithValue;
					unsigned int number(1);
					auto&& attributesIterator = numberOfPersonWithValueOfDiscreteAttribute.find(headers[i]);
					if (attributesIterator != numberOfPersonWithValueOfDiscreteAttribute.end())
					{
						numberOfPersonsWithValue = attributesIterator->second;
						auto&& valuesIterator = attributesIterator->second.find(line[i]);
						if (valuesIterator != attributesIterator->second.end())
						{
							number = valuesIterator->second;
						}
					}
					numberOfPersonsWithValue.insert({ line[i], number });
					numberOfPersonWithValueOfDiscreteAttribute.insert({ headers[i], numberOfPersonsWithValue });
				}
			}
		}
		else
		{
			// Sick patient
			map<string, vector<double>> illContinuousAttribute;
			map<string, vector<string>> illDiscreteAttribute;

			auto && illContinuousAttributeIterator = continuousAttributesForDisease.find(disease);
			auto && illDiscreteContinuousAttributeIterator = discreteAttributesForDisease.find(disease);

			if (illContinuousAttributeIterator != continuousAttributesForDisease.end())
			{
				illContinuousAttribute = illContinuousAttributeIterator->second;
			}
			if (illDiscreteContinuousAttributeIterator != discreteAttributesForDisease.end())
			{
				illDiscreteAttribute = illDiscreteContinuousAttributeIterator->second;
			}

			for (unsigned int i = 0; i < headersSize; ++i)
			{
				auto&& attribute = continuousAttributes.find(headers[i]);
				if (attribute != continuousAttributes.end())
				{
					try
					{
						double value = stod(line[i]);
						auto&& valuesIterator = illContinuousAttribute.find(headers[i]);
						if (valuesIterator != illContinuousAttribute.end())
						{
							valuesIterator->second.push_back(value);
						}
						else
						{
							illContinuousAttribute.insert({ headers[i], { value } });
						}
					}
					catch (invalid_argument)
					{
						QString message("Value ");
						message += QString::fromStdString(line[i]) + QString(" is not a number.");
						Log::info(message.toStdString());
						return false;
					}
				}
				else
				{
					auto&& attribute = discreteAttributes.find(headers[i]);
					if (attribute == discreteAttributes.end())
					{
						QString message("No header found for ");
						message += QString::fromStdString(headers[i]);
						Log::info(message.toStdString());
						return false;
					}
					auto&& valuesIterator = illDiscreteAttribute.find(headers[i]);
					if (valuesIterator != illDiscreteAttribute.end())
					{
						valuesIterator->second.push_back(line[i]);
					}
					else
					{
						illDiscreteAttribute.insert({ headers[i], {line[i] } });
					}

					map<string, unsigned int> numberOfPersonsWithValue;
					unsigned int number(1);
					auto&& attributesIterator = numberOfPersonWithValueOfDiscreteAttribute.find(headers[i]);
					if (attributesIterator != numberOfPersonWithValueOfDiscreteAttribute.end())
					{
						numberOfPersonsWithValue = attributesIterator->second;
						auto&& valuesIterator = attributesIterator->second.find(line[i]);
						if (valuesIterator != attributesIterator->second.end())
						{
							number = valuesIterator->second;
						}
					}
					numberOfPersonsWithValue.insert({ line[i], number });
					numberOfPersonWithValueOfDiscreteAttribute.insert({ headers[i], numberOfPersonsWithValue });
				}
			}
			continuousAttributesForDisease.emplace(disease, illContinuousAttribute);
			discreteAttributesForDisease.emplace(disease, illDiscreteAttribute);
		}
	}

	// Computing normal intervals
	map<string, shared_ptr<ContinuousAttribute>> continuousNormalIntervals;
	unsigned int attributeId = 1;
	for (auto&& continuousAttribute : healthyContinuousAttributes)
	{
		double sum = 0, average = 0, standardDeviation = 0;
		unsigned int dataNumber = continuousAttribute.second.size();
		if (dataNumber == 0)
		{
			QString message("No data for attribute ");
			message += QString::fromStdString(continuousAttribute.first);
			Log::info(message.toStdString());
			return false;
		}
		for (auto&& value : continuousAttribute.second)
		{
			sum += value;
		}
		average = sum / dataNumber;
		for (auto && value : continuousAttribute.second)
		{
			standardDeviation += pow(value - average, 2);
		}
		standardDeviation = sqrt(standardDeviation / dataNumber);
		continuousNormalIntervals.emplace(continuousAttribute.first, std::make_shared<ContinuousAttribute>(attributeId, continuousAttribute.first, vector<pair<double, double>>{ {average - 2 * standardDeviation, average + 2 * standardDeviation}}));
		++attributeId;
	}

	// Computing discriminant attributes
	vector<Disease> diseases;
	unsigned int diseaseId(1);
	for (auto&& iterator : continuousAttributesForDisease)
	{
		string diseaseName = iterator.first;
		map<string, vector<double>> attributes = iterator.second;
		vector<shared_ptr<Attribute>> discriminantAttributes;
		for (auto&& attribute : attributes)
		{
			auto&& normalAttribute = continuousNormalIntervals.find(attribute.first);
			if (normalAttribute == continuousNormalIntervals.end())
			{
				QString message("No header found for ");
				message += QString::fromStdString(attribute.first);
				Log::info(message.toStdString());
				return false;
			}
			double abnormalNumber(0);
			for (auto&& value : attribute.second)
			{
				if (!normalAttribute->second->isInNormalInterval(value))
				{
					++abnormalNumber;
				}
			}
			if (abnormalNumber / attribute.second.size() > 0.8)
			{
				discriminantAttributes.emplace_back(normalAttribute->second);
			}
		}
		diseases.emplace_back(diseaseId, diseaseName, discriminantAttributes);
		++diseaseId;
	}

	for (auto&& iterator : discreteAttributesForDisease)
	{
		string diseaseName = iterator.first;
		map<string, vector<string>> attributes = iterator.second;
		vector<shared_ptr<Attribute>> discriminantAttributes;

		Disease* disease = Disease::diseaseWithNameFromVector(diseaseName, diseases);
		if (disease != nullptr)
		{
			discriminantAttributes = disease->getDiscriminantAttributes();
		}

		for (auto&& attribute : attributes)
		{
			map<string, unsigned int> valueNumber;
			for (auto&& value : attribute.second)
			{
				unsigned int number(1);
				auto&& iterator = valueNumber.find(value);
				if (iterator != valueNumber.end())
				{
					number = iterator->second;
				}
				valueNumber.insert({ value, number });
			}

			auto&& totalValueNumberIterator = numberOfPersonWithValueOfDiscreteAttribute.find(attribute.first);
			if (totalValueNumberIterator == numberOfPersonWithValueOfDiscreteAttribute.end())
			{
				QString message("No total value number found for disease ");
				message += QString::fromStdString(attribute.first);
				Log::info(message.toStdString());
				return false;
			}
			map <string, unsigned int> totalValueNumber = totalValueNumberIterator->second;

			for (auto&& valueNumberIterator = valueNumber.begin(); valueNumberIterator != valueNumber.end();)
			{
				if (valueNumberIterator->second < 10)
				{
					valueNumber.erase(valueNumberIterator++);
					continue;
				}
				
				auto&& totalValueNumberForAttributeIterator = totalValueNumber.find(valueNumberIterator->first);
				if (totalValueNumberForAttributeIterator == totalValueNumber.end())
				{
					QString message("No total value number found for disease ");
					message += QString::fromStdString(attribute.first) + QString::fromStdString(" and attribute ") + QString::fromStdString(valueNumberIterator->first);
					Log::info(message.toStdString());
					return false;
				}
				if (static_cast<double>(valueNumberIterator->second) / static_cast<double>(totalValueNumberForAttributeIterator->second) >= 0.9)
				{
					discriminantAttributes.push_back(static_pointer_cast<Attribute>(make_shared<DiscreteAttribute>(attributeId, attribute.first)));
				}
				valueNumberIterator++;
			}
		}

		if (disease == nullptr)
		{
			diseases.emplace_back(diseaseId, diseaseName, discriminantAttributes);
			++diseaseId;
		}
	}

	DbManager db("DiseaseForecasterServer.db");
	return db.insertIntoDatabase(diseases);
}