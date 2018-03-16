// System include
#include <iostream>
#include <string>
#include <map>

using namespace std;

// Personnal include
#include "PotentialDisease.h"

// Constructor
PotentialDisease::PotentialDisease(int id, string name, double matchingRate, map<string, double> continuousAttributesValues, map<string,string> discreteAttributesValues)
	: id(id), name(name), matchingRate(matchingRate), continuousAttributesValues(continuousAttributesValues), discreteAttributesValues(discreteAttributesValues)
{
	#ifdef DEBUG
		cout << "PotentialDisease constructor call" << endl;
	#endif // DEBUG
}

// Destructor
PotentialDisease::~PotentialDisease()
{
	#ifdef DEBUG
		cout << "PotentialDisease destructor call" << endl;
	#endif // DEBUG
}

//Other
string PotentialDisease::displayContent(bool printOnScreen)
{
	string message = "";

	message += "Disease name : " + name + "\n";
	message += "Matching rate : " + to_string(matchingRate) + "\n";;
	for (auto const& continuousAttributeValue : continuousAttributesValues)
	{
		message += continuousAttributeValue.first +  " " + to_string(continuousAttributeValue.second) + "\n";
	}
	for (auto const& discreteAttributesValue : discreteAttributesValues)
	{
		message += discreteAttributesValue.first + " " + discreteAttributesValue.second + "\n";
	}

	if (printOnScreen)
		cout << message;

	return message;
}

int PotentialDisease::getId()
{
	return id;
}
map<string, double> PotentialDisease::getContinuousAttributesValues()
{
	return continuousAttributesValues;
}
map<string, string> PotentialDisease::getDiscreteAttributesValues()
{
	return discreteAttributesValues;
}
string PotentialDisease::getName()
{
	return name;
}
double PotentialDisease::getMatchingRate()
{
	return matchingRate;
}
