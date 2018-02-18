// System include
#include <iostream>
using namespace std;

// Personnal include
#include "Analyse.h"

// Constants

// Constructors
Analyse::Analyse(HealthPrint healthPrint, vector<PotentialDisease> diseases) : healthPrint(healthPrint), diseases(diseases)
{
	#ifdef DEBUG
		cout << "Analyse constructor call" << endl;
	#endif // DEBUG
}

// Destructor
Analyse::~Analyse()
{
	#ifdef DEBUG
		cout << "Analyse destructor call" << endl;
	#endif // DEBUG
}