#ifndef MODELIMPORTER_H
#define MODELIMPORTER_H

// System include
#include <map>
#include <vector>
#include <set>
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

	set<string> continuousAttributes;
	set<string> discreteAttributes;

	// Methods
public:
	// Constructors
	ModelImporter(string pathToDescriptionFile, string pathToValuesFile);

	// Destructors
	~ModelImporter();

	// Others
	set<string>& getContinuousAttributes() { return continuousAttributes; }
	set<string>& getDiscreteAttributes() { return discreteAttributes; }

	bool importModel();

private:
	bool importAttributeNames();
	bool importAttributeValues();
};

#endif // MODELIMPORTER_H