#ifndef MODELIMPORTER_H
#define MODELIMPORTER_H

// System include
#include <map>
#include <vector>
using namespace std;

// Personnal include

// Constants

// Types

// Class
class ModelImporter
{
	// Attributes
private:
	const string pathToDescriptionFile;
	const string pathToValuesFile;

	map<string, vector<double>> continuousAttributes;
	map<string, vector<string>> discreteAttributes;

	// Methods
public:
	// Constructors
	ModelImporter(string pathToDescriptionFile, string pathToValuesFile);

	// Destructors
	~ModelImporter();

	// Others
	map<string, vector<double>>& getContinuousAttributes() { return continuousAttributes; }
	map<string, vector<string>>& getDiscreteAttributes() { return discreteAttributes; }

	bool importModel();

private:
	bool importAttributeNames();
	bool importAttributeValues();
};

#endif // MODELIMPORTER_H