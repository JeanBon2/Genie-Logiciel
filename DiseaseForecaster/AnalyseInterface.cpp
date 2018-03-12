// System include
#include <iostream>
using namespace std;

// Personnal include
#include "AnalyseInterface.h"
#include "CsvParser.h"
#include <QFile>
#include <typeinfo>
#include <string>
#include <stdlib.h>

// Constants

void AnalyseInterface::displayInterfaceText()
{

}

void AnalyseInterface::run()
{

}

vector<Analyse> AnalyseInterface::AnalysePrintFile(string filePath)
{
  vector<Analyse> analyses;
  vector<HealthPrint*> healthPrints = getHealthPrintFromFile(filePath);

  cout << "==========================" << endl;
  for (auto&& it :healthPrints)
  {
    it->displayContent();
    cout << endl;
  }

  // 2. Get all Diseases

  // 3. Analyse

  /*
  for (auto&& it :healthPrints)
  {
    for (auto&& it2 : it)
    {
      cout << "avant" << endl;
      cout << it2 << endl;
      cout << "après" << endl;
    }
  }*/
    return analyses;
}

vector<Analyse> AnalyseInterface::AnalysePrintFolder(string folderPath)
{

}


// Constructors
AnalyseInterface::AnalyseInterface()
{
  cout << "Constructeur" << endl;
}

// Destructors
AnalyseInterface::~AnalyseInterface()
{
  cout << "Destructeur" << endl;
}

// Private
vector<HealthPrint*> AnalyseInterface::getHealthPrintFromFile(string filePath)
{
  // 1. Get HealthPrints from file
  QFile file(QString::fromStdString(filePath));
	vector<vector<string>> healthPrintsFromFile =  CsvParser::staticParse(file);

  vector<vector<string>>::iterator it;
  vector<string>::iterator it2;
  vector<HealthPrint*> healthPrints;
  vector<string> attributesTitle;

  map<string, double> continuousAttributesValues;
  map<string, string> discreteAttributesValues;

  int i = 0;
  for (it = healthPrintsFromFile.begin(); it != healthPrintsFromFile.end(); ++it) // Because the first line isn't a HealthPrint
  {
    int j = 0;
    for (it2 = it->begin(); it2 != it->end(); ++it2)
    {
        if (i == 0)
        {
          cout << *it2 << endl;
          attributesTitle.push_back(*it2);
          continue;
        }

        double numericAttribute;
        string strAttribute;
        //std::string::size_type sz;

        strAttribute = *it2;
        try {
          numericAttribute = stod(strAttribute);
          cout << "Insert Double : " << attributesTitle[j] << " " << j << endl;
          cout  << " " << numericAttribute << endl;
          continuousAttributesValues.insert(std::pair<string, double>(attributesTitle[j], numericAttribute));
        }
        catch ( const std::exception & e )
        {
          cout << "Insert String : " << attributesTitle[j] << " " << j << " " << strAttribute << endl;
          discreteAttributesValues.insert(std::pair<string, string>(attributesTitle[j], strAttribute));
        }

        j++;
    }
    cout << endl; //TODO REMOVE
    if (i > 0)
      healthPrints.push_back(new HealthPrint(i, "unnamed", "unnamed", "nodate", -1, continuousAttributesValues, discreteAttributesValues));

    continuousAttributesValues.clear();
    discreteAttributesValues.clear();
    i++;
  }

  for (auto&& it : attributesTitle)
  {
    cout << it << endl;
  }

  return healthPrints;
}
