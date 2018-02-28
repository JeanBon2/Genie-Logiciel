#pragma once
#ifndef POTENTIALDISEASE_H
#define POTENTIALDISEASE_H

// System include
using namespace std;
#include <map>

// Class
class PotentialDisease
{
	// Attributes
private:
	//double privateAttribute;
	map<string, double> continuousAttributesValues;
	map<string, string> discreteAttributesValues;
	string name;
	double matchingRate;


	// Methods
public:
	// Constructors
	PotentialDisease(string name, double matchingRate, map<string, double> continuousAttributesValues, map<string, string> discreteAttributesValues);

	// Destructors
	~PotentialDisease();

	//Others
	void displayContent();

};

#endif // POTENTIALDISEASE_H
