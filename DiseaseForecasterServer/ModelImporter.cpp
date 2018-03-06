// System include
#include <algorithm>
#include <utility>
using namespace std;

// Personnal include
#include "ModelImporter.h"
#include "CsvParser.h"

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
		// LOG
		return false;
	}

	return true;
}

// Private methods
bool ModelImporter::importAttributeNames()
{
	QFile descriptionFile(QString::fromStdString(pathToDescriptionFile));
	vector<vector<string>> attributes = CsvParser::staticParse(pathToDescriptionFile);
	if (attributes.empty())
	{
		// LOG
		return false;
	}
	vector<string>& descriptions = attributes[0];
	attributes.erase(attributes.begin());
	if (descriptions.size() != 2)
	{
		// LOG
		return false;
	}

	string attributeNameHeader = descriptions[0];
	string attributeTypeHeader = descriptions[1];
	std::transform(attributeNameHeader.begin(), attributeNameHeader.end(), attributeNameHeader.begin(), ::tolower);
	std::transform(attributeTypeHeader.begin(), attributeTypeHeader.end(), attributeTypeHeader.begin(), ::tolower);
	if (attributeNameHeader != "attributename" || attributeTypeHeader != "attributetype")
	{
		// LOG
		return false;
	}

	for (auto&& line : attributes)
	{
		if (line.size() != 2)
		{
			// LOG
			return false;
		}

		const string& attributeName = line[0];
		const string& attributeType = line[1];

		if (attributeType == "String" || attributeType == "string")
		{
			// Attribut discret
			discreteAttributes.emplace(attributeName, vector<string>());
		}
		else
		{
			// Attribut continu
			continuousAttributes.emplace(attributeName, vector<double>());
		}
	}


	return true;
}
bool ModelImporter::importAttributeValues()
{
	
	return true;
}