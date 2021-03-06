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
	Analyse(int id, HealthPrint& healthPrint, vector<PotentialDisease> diseases);

	//Others
    int getId() { return id; }
    void setId(int id) {this->id = id;}

	void displayContent();
	void displayHeader();
    HealthPrint& getHealthPrint();
	vector<PotentialDisease> getDiseases();

};

#endif // ANALYSE_H
