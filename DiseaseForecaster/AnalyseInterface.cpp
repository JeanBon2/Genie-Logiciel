// System include
#include <iostream>
#include <QFile>
#include <typeinfo>
#include <string>
#include <QDirIterator>
using namespace std;

// Personnal include
#include "AnalyseInterface.h"
#include "CsvParser.h"
#include "ContinuousAttribute.h"
#include "DiscreteAttribute.h"

// Constants

void AnalyseInterface::displayInterfaceText()
{
  cout << "Effectuer une Analyse" << endl;
  cout << "1. Analyser un fichier d'empreintes" << endl;
  cout << "2. Analyser un dossier d'empreintes" << endl;
}

void AnalyseInterface::run()
{
  int choice;
  string path;

  displayInterfaceText();

  cin >> choice;

  cout << "Saisir le chemin : ";
  cin >> path;

  if (choice == 1)
    AnalysePrintFile(path);
  else if (choice == 2)
    AnalysePrintFolder(path);
}

void AnalyseInterface::AnalysePrintFile(string filePath)
{
  vector<Analyse> analyses;

  vector<HealthPrint*> healthPrints = getHealthPrintFromFile(filePath);

  // 2. Get all Diseases
  vector<Disease> diseases = getAllDiseases();
  vector<ContinuousAttribute> continuousAttributes;
  vector<DiscreteAttribute> discreteAttributes;


  // 3. Analyse
  for (auto&& hp : healthPrints)
  {
    vector<PotentialDisease> potencialDiseases;
    map<string, double> continuousAttributesValues;
    map<string, string> discreteAttributesValues;

    for (auto&& dis : diseases)
    {
      double nbAnormalAttributes = 0;
      double nbAttributes = 0;

      for (auto&& hpAttribute : hp->getContinuousAttributesValues())
      {
        bool succes = false;
        shared_ptr<Attribute>  att = dis.isDiscriminantByName(hpAttribute.first, succes);

        if (succes)
        {
            vector<interval> inter = db.getNormalIntervalsForContinuousAttribute(hpAttribute.first);
            if (hpAttribute.second > inter[0].first &&
                hpAttribute.second < inter[0].second)
            {
              continuousAttributesValues.insert(hpAttribute);
              nbAnormalAttributes++;
            }
        }

        nbAttributes++;
      }
      for (auto&& hpAttribute : hp->getDiscreteAttributesValues())
      {
        bool succes = false;
        shared_ptr<Attribute>  att = dis.isDiscriminantByName(hpAttribute.first, succes);

        if (succes)
        {
          vector<string> normalValues = db.getNormalValuesForDiscreteAttribute(hpAttribute.first);

          for (auto&& normalValue : normalValues)
          {
            if (normalValue == hpAttribute.second)
            {
              discreteAttributesValues.insert(hpAttribute);
              nbAnormalAttributes++;
              break;
            }
          }
        }

        nbAttributes++;
      }

      double matchingRate = nbAttributes / nbAnormalAttributes;
      if ( matchingRate > 0.8)
      {
        PotentialDisease potencialdisease(0, dis.getName(), matchingRate, continuousAttributesValues, discreteAttributesValues);
        potencialDiseases.push_back(potencialdisease);
      }
    }

    Analyse analyse(0, *hp, potencialDiseases);
    analyses.push_back(analyse);
  }

  // 4. INSERTION DES RÉSULTATS
  for (auto&& it : analyses)
  {
      db.insertAnalyse(it);
  }
}

void AnalyseInterface::AnalysePrintFolder(string folderPath)
{
  QDirIterator it(QString::fromStdString(folderPath), QStringList() << "*.txt", QDir::Files, QDirIterator::Subdirectories);

  while (it.hasNext())
  {
      AnalysePrintFile(it.next().toStdString());
  }
}


// Constructors
AnalyseInterface::AnalyseInterface()
: db("DiseaseForecaster.db")
{
  #ifdef DEBUG
		cout << "Analyse constructor call" << endl;
	#endif // DEBUG
}

// Destructors
AnalyseInterface::~AnalyseInterface()
{
  #ifdef DEBUG
		cout << "Analyse destructor call" << endl;
	#endif // DEBUG
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
          //cout << *it2 << endl;
          attributesTitle.push_back(*it2);
          continue;
        }

        double numericAttribute;
        string strAttribute;
        //std::string::size_type sz;

        strAttribute = *it2;
        try {
          numericAttribute = stod(strAttribute);
          //cout << "Insert Double : " << attributesTitle[j] << " " << j << endl;
          //cout  << " " << numericAttribute << endl;
          continuousAttributesValues.insert(std::pair<string, double>(attributesTitle[j], numericAttribute));
        }
        catch ( const std::exception & e )
        {
          //cout << "Insert String : " << attributesTitle[j] << " " << j << " " << strAttribute << endl;
          discreteAttributesValues.insert(std::pair<string, string>(attributesTitle[j], strAttribute));
        }

        j++;
    }
    if (i > 0)
      healthPrints.push_back(new HealthPrint(i, "unnamed", "unnamed", "nodate", -1, continuousAttributesValues, discreteAttributesValues));

    continuousAttributesValues.clear();
    discreteAttributesValues.clear();
    i++;
  }

  return healthPrints;
}

vector<Disease> AnalyseInterface::getAllDiseases()
{
  vector<Disease> diseases = db.getDiseases();

  for (auto&& it : diseases)
  {
    //cout << "ligne " << it.getId() << " " << it.getName() << endl;
    vector<shared_ptr<Attribute>> attributes = db.getDiscriminantAttributesForDisease(it.getId());

    for (auto&& it2 : attributes)
    {
      it.addDiscriminantAttribute(it2);
    }
  }

  return diseases;
}
