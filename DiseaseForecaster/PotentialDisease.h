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
	string displayContent(bool printOnScreen = true);

    int getId();
    void setId(int id) {this->id = id;}

	map<string, double> getContinuousAttributesValues();
	map<string, string> getDiscreteAttributesValues();
	string getName();
	double getMatchingRate();

};

#endif // POTENTIALDISEASE_H
