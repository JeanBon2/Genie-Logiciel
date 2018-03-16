#ifndef ANALYSEINTERFACE_H
#define ANALYSEINTERFACE_H

// System include
#include <iostream>
#include <vector>
using namespace std;

// Personnal include
#include "Analyse.h"

// Class
class AnalyseInterface
{
	// Methods
public:
	// Constructors
	AnalyseInterface();

	// Destructors
	virtual ~AnalyseInterface();

//protected:

  void displayInterfaceText();

  void run();

  vector<Analyse> AnalysePrintFile(string filePath);

  vector<Analyse> AnalysePrintFolder(string folderPath);

private:
	vector<HealthPrint*> getHealthPrintFromFile(string filePath);

};

#endif // ANALYSEINTERFACE_H
