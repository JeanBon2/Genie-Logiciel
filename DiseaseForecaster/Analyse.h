#pragma once
#ifndef ANALYSE_H
#define ANALYSE_H

// System include
using namespace std;
#include <iostream>
#include <vector>

// Personnal include
#include "HealthPrint.h"
#include "PotentialDisease.h"

// Class
class Analyse
{
	// Attributes
private:
	HealthPrint healthPrint;
	vector<PotentialDisease> diseaess;

	// Methods
public:
	// Constructors
	Analyse(HealthPrint healthPrint, vector<PotentialDisease> diseaese);

	// Destructors
	~Analyse();

};

#endif // ANALYSE_H
