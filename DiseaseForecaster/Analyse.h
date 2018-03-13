#pragma once
#ifndef ANALYSE_H
#define ANALYSE_H

// System include
using namespace std;
#include <vector>

// Personnal include
#include "HealthPrint.h"
#include "PotentialDisease.h"

// Class
class Analyse
{
	// Attributes
private:
	int id;
	HealthPrint& healthPrint;
	vector<PotentialDisease> diseases;

	// Methods
public:
	// Constructor
	Analyse(int id, HealthPrint& healthPrint, vector<PotentialDisease> diseases = vector<PotentialDisease>());

	// Destructor
	~Analyse();

	int getId() { return id; }

	HealthPrint& getHealthprint() { return healthPrint; }

	//Others
	void displayContent();
	void displayHeader();
	int getId();
	HealthPrint getHealthPrint();
	vector<PotentialDisease> getDiseases();

};

#endif // ANALYSE_H
