// System include
#include <iostream>
#include <string>
using namespace std;

// Personnal include
#include "Analyse.h"

// Constructor
Analyse::Analyse(int id, HealthPrint healthPrint, vector<PotentialDisease> diseases) : 
	id(id), healthPrint(healthPrint), diseases(diseases)
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

// Others
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