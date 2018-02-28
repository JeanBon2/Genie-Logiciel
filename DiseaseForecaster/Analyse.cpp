// System include
#include <iostream>
#include <string>
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
void Analyse::displayContent()
{
	healthPrint.displayContent();
	for (PotentialDisease& potentialDisease : diseases)
	{
		potentialDisease.displayContent();
	}
}
void Analyse::displayHeader()
{
	cout << healthPrint.getPatientName() << " - " << healthPrint.getPrintDate().toString("dd.MM.yyyy").toUtf8().constData() << endl;
}