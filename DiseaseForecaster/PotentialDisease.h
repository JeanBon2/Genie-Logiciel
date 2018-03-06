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
	int id;
	map<string, double> continuousAttributesValues;
	map<string, string> discreteAttributesValues;
	string name;
	double matchingRate;


	// Methods
public:
	// Constructor
	PotentialDisease(int id, string name, double matchingRate, map<string, double> continuousAttributesValues, map<string, string> discreteAttributesValues);

	// Destructor
	~PotentialDisease();

	//Other
	void displayContent();

};

#endif // POTENTIALDISEASE_H
