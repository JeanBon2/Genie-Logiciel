// System include
using namespace std;
#include <iostream>
#include <string>
#include <map>

// Personnal include
#include "PotentialDisease.h"

// Constructors
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
//Others
void PotentialDisease::displayContent()
{
	cout <<"Disease name : "<< name << endl;
	cout <<"Matching rate : " << matchingRate<< endl;
	for (auto const& continuousAttributeValue : continuousAttributesValues)
	{
		cout << continuousAttributeValue.first << " "<< continuousAttributeValue.second << endl;
	}
}