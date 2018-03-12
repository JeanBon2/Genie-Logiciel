#ifndef THEALTHPRINT_H
#define THEALTHPRINT_H

// System include
#include <iostream>
using namespace std;

// Personnal include
#include "c:\Users\asduc.INSA-LYON\Documents\G�nie logiciel\Genie-Logiciel\DiseaseForecaster\tests\AbstractTest.h"
#include "c:\Users\asduc.INSA-LYON\Documents\G�nie logiciel\Genie-Logiciel\DiseaseForecaster\tests\MethodTest.h"
#include "HealthPrint.h"

// Constants

// Types
class THealthPrint;

class THealthPrintMethod : public MethodTest
{
public:
    THealthPrintMethod(THealthPrint* tmp)
     :outter(tmp)
     {}
 protected:
     THealthPrint* outter;
 };

// Class
class THealthPrint : public AbstractTest
{
public:
   // Class constructor
   THealthPrint() {}

   // This Method add every test method in the run engine
   void init ()
   {
       addTest(new HealthPrintTest(this));
       addTest(new displayContentTest(this));
       addTest(new getPatientNameTest(this));
       addTest(new getPrintDateTest(this));
       addTest(new analyseTest(this));
   }

   /*
   Here you can add one event method to handle your tests variables and objects.
    Like beforeEachTest() or afterClass()
   */

   // Test class for the method HealthPrint of class HealthPrint
   class HealthPrintTest : public THealthPrintMethod
   {
   public:
       HealthPrintTest(THealthPrint* tmp): THealthPrintMethod(tmp) { testResult.name = "HealthPrintTest"; }
       TestResult execute()
        {
		   cout << "Test de cr�ation d'un objet HealthPrint" << endl;
		   
		   int idTest;
		   string patientNameTest;
		   string doctorNameTest;
		   string printDateTest;
		   int sensorIdTest;
		   map<string, double> continuousAttributesValuesTest;
		   map<string, string> discreteAttributesValuesTest;

		   //Test de cr�ation d'un objet HealthPrint avec des param�tres corrects
		   cout << "Saisir un id d'empreinte : ";
		   cin >> idTest;

		   cout << "Saisir un nom de patient : ";
		   cin >> patientNameTest;

		   cout << "Saisir un nom de docteur : ";
		   cin >> doctorNameTest;

		   cout << "Saisir une date de saisie de l'empreinte : ";
		   cin >> printDateTest;

		   cout << "Saisir un id de capteur r�alisant l'empreinte : ";
		   cin >> sensorIdTest;

		   // continuousAttributesValuesTest[nameTest] = matchingRateTest;

		   // discreteAttributesValuesTest[nameTest] = matchingRateTest;

		   HealthPrint healthPrint1(idTest, patientNameTest, doctorNameTest, printDateTest, sensorIdTest,
			   continuousAttributesValuesTest, discreteAttributesValuesTest);


		   // Test de cr�ation d'un objet HealthPrint avec un id d'empreinte d�j� existant
		   cout << "Saisir un id d'empreinte existant : ";
		   cin >> idTest;

		   cout << "Saisir un nom de patient : ";
		   cin >> patientNameTest;

		   cout << "Saisir un nom de docteur : ";
		   cin >> doctorNameTest;

		   cout << "Saisir une date de saisie de l'empreinte : ";
		   cin >> printDateTest;

		   cout << "Saisir un id de capteur r�alisant l'empreinte : ";
		   cin >> sensorIdTest;

		   // continuousAttributesValuesTest[nameTest] = matchingRateTest;

		   // discreteAttributesValuesTest[nameTest] = matchingRateTest;

		   HealthPrint healthPrint2(idTest, patientNameTest, doctorNameTest, printDateTest, sensorIdTest,
			   continuousAttributesValuesTest, discreteAttributesValuesTest);


		   // Test de cr�ation d'un objet HealthPrint avec un nom de patient incorrect
		   cout << "Saisir un id d'empreinte : ";
		   cin >> idTest;

		   cout << "Saisir un nom de patient contenant des chiffres : ";
		   cin >> patientNameTest;

		   cout << "Saisir un nom de docteur : ";
		   cin >> doctorNameTest;

		   cout << "Saisir une date de saisie de l'empreinte : ";
		   cin >> printDateTest;

		   cout << "Saisir un id de capteur r�alisant l'empreinte : ";
		   cin >> sensorIdTest;

		   // continuousAttributesValuesTest[nameTest] = matchingRateTest;

		   // discreteAttributesValuesTest[nameTest] = matchingRateTest;

		   HealthPrint healthPrint3(idTest, patientNameTest, doctorNameTest, printDateTest, sensorIdTest,
			   continuousAttributesValuesTest, discreteAttributesValuesTest);


		   // Test de cr�ation d'un objet HealthPrint avec un nom de docteur incorrect
		   cout << "Saisir un id d'empreinte : ";
		   cin >> idTest;

		   cout << "Saisir un nom de patient : ";
		   cin >> patientNameTest;

		   cout << "Saisir un nom de docteur contenant des chiffres : ";
		   cin >> doctorNameTest;

		   cout << "Saisir une date de saisie de l'empreinte : ";
		   cin >> printDateTest;

		   cout << "Saisir un id de capteur r�alisant l'empreinte : ";
		   cin >> sensorIdTest;

		   // continuousAttributesValuesTest[nameTest] = matchingRateTest;

		   // discreteAttributesValuesTest[nameTest] = matchingRateTest;

		   HealthPrint healthPrint4(idTest, patientNameTest, doctorNameTest, printDateTest, sensorIdTest,
			   continuousAttributesValuesTest, discreteAttributesValuesTest);


		   // Test de cr�ation d'un objet HealthPrint avec une date impossible
		   cout << "Saisir un id d'empreinte : ";
		   cin >> idTest;

		   cout << "Saisir un nom de patient : ";
		   cin >> patientNameTest;

		   cout << "Saisir un nom de docteur : ";
		   cin >> doctorNameTest;

		   cout << "Saisir une date de saisie de l'empreinte impossible : ";
		   cin >> printDateTest;

		   cout << "Saisir un id de capteur r�alisant l'empreinte : ";
		   cin >> sensorIdTest;

		   // continuousAttributesValuesTest[nameTest] = matchingRateTest;

		   // discreteAttributesValuesTest[nameTest] = matchingRateTest;

		   HealthPrint healthPrint5(idTest, patientNameTest, doctorNameTest, printDateTest, sensorIdTest,
			   continuousAttributesValuesTest, discreteAttributesValuesTest);


		   // Test de cr�ation d'un objet HealthPrint avec une date contenant des lettres
		   cout << "Saisir un id d'empreinte : ";
		   cin >> idTest;

		   cout << "Saisir un nom de patient : ";
		   cin >> patientNameTest;

		   cout << "Saisir un nom de docteur : ";
		   cin >> doctorNameTest;

		   cout << "Saisir une date de saisie de l'empreinte avec des lettres : ";
		   cin >> printDateTest;

		   cout << "Saisir un id de capteur r�alisant l'empreinte : ";
		   cin >> sensorIdTest;

		   // continuousAttributesValuesTest[nameTest] = matchingRateTest;

		   // discreteAttributesValuesTest[nameTest] = matchingRateTest;

		   HealthPrint healthPrint6(idTest, patientNameTest, doctorNameTest, printDateTest, sensorIdTest,
			   continuousAttributesValuesTest, discreteAttributesValuesTest);


		   // Test de cr�ation d'un objet HealthPrint avec un id de capteur inexistant
		   cout << "Saisir un id d'empreinte : ";
		   cin >> idTest;

		   cout << "Saisir un nom de patient : ";
		   cin >> patientNameTest;

		   cout << "Saisir un nom de docteur : ";
		   cin >> doctorNameTest;

		   cout << "Saisir une date de saisie de l'empreinte avec des lettres : ";
		   cin >> printDateTest;

		   cout << "Saisir un id de capteur inexistant : ";
		   cin >> sensorIdTest;

		   // continuousAttributesValuesTest[nameTest] = matchingRateTest;

		   // discreteAttributesValuesTest[nameTest] = matchingRateTest;

		   HealthPrint healthPrint7(idTest, patientNameTest, doctorNameTest, printDateTest, sensorIdTest,
			   continuousAttributesValuesTest, discreteAttributesValuesTest);

           return testResult;
        }
   };

   // Test class for the method displayContent of class HealthPrint
   class displayContentTest : public THealthPrintMethod
   {
   public:
       displayContentTest(THealthPrint* tmp): THealthPrintMethod(tmp) { testResult.name = "displayContentTest"; }
       TestResult execute()
        {
		   cout << "Test d'affichage du contenu d'un objet HealthPrint" << endl;
		   int idTest;
		   string patientNameTest;
		   string doctorNameTest;
		   string printDateTest;
		   int sensorIdTest;
		   map<string, double> continuousAttributesValuesTest;
		   map<string, string> discreteAttributesValuesTest;

		   // Cr�ation d'un objet HealthPrint avec des param�tres corrects
		   cout << "Saisir un id d'empreinte : ";
		   cin >> idTest;

		   cout << "Saisir un nom de patient : ";
		   cin >> patientNameTest;

		   cout << "Saisir un nom de docteur : ";
		   cin >> doctorNameTest;

		   cout << "Saisir une date de saisie de l'empreinte : ";
		   cin >> printDateTest;

		   cout << "Saisir un id de capteur r�alisant l'empreinte : ";
		   cin >> sensorIdTest;

		   // continuousAttributesValuesTest[nameTest] = matchingRateTest;

		   // discreteAttributesValuesTest[nameTest] = matchingRateTest;

		   HealthPrint healthPrint1(idTest, patientNameTest, doctorNameTest, printDateTest, sensorIdTest,
			   continuousAttributesValuesTest, discreteAttributesValuesTest);


		   // Cr�ation d'un objet HealthPrint avec un id d'empreinte d�j� existant
		   cout << "Saisir un id d'empreinte existant : ";
		   cin >> idTest;

		   cout << "Saisir un nom de patient : ";
		   cin >> patientNameTest;

		   cout << "Saisir un nom de docteur : ";
		   cin >> doctorNameTest;

		   cout << "Saisir une date de saisie de l'empreinte : ";
		   cin >> printDateTest;

		   cout << "Saisir un id de capteur r�alisant l'empreinte : ";
		   cin >> sensorIdTest;

		   // continuousAttributesValuesTest[nameTest] = matchingRateTest;

		   // discreteAttributesValuesTest[nameTest] = matchingRateTest;

		   HealthPrint healthPrint2(idTest, patientNameTest, doctorNameTest, printDateTest, sensorIdTest,
			   continuousAttributesValuesTest, discreteAttributesValuesTest);


		   // Test d'affichage d'un objet HealthPrint avec des param�tres corrects
		   healthPrint1.displayContent();

		   // Test d'affichage d'un objet HealthPrint avec des apram�tres incorrects
		   healthPrint2.displayContent();

           return testResult;
        }
   };

   // Test class for the method getPatientName of class HealthPrint
   class getPatientNameTest : public THealthPrintMethod
   {
   public:
       getPatientNameTest(THealthPrint* tmp): THealthPrintMethod(tmp) { testResult.name = "getPatientNameTest"; }
       TestResult execute()
        {
		   cout << "Test de r�cup�ration du nom du patient d'un objet HealthPrint" << endl;

		   int idTest;
		   string patientNameTest;
		   string doctorNameTest;
		   string printDateTest;
		   int sensorIdTest;
		   map<string, double> continuousAttributesValuesTest;
		   map<string, string> discreteAttributesValuesTest;

		   // Cr�ation d'un objet HealthPrint avec des param�tres corrects
		   cout << "Saisir un id d'empreinte : ";
		   cin >> idTest;

		   cout << "Saisir un nom de patient : ";
		   cin >> patientNameTest;

		   cout << "Saisir un nom de docteur : ";
		   cin >> doctorNameTest;

		   cout << "Saisir une date de saisie de l'empreinte : ";
		   cin >> printDateTest;

		   cout << "Saisir un id de capteur r�alisant l'empreinte : ";
		   cin >> sensorIdTest;

		   // continuousAttributesValuesTest[nameTest] = matchingRateTest;

		   // discreteAttributesValuesTest[nameTest] = matchingRateTest;

		   HealthPrint healthPrint1(idTest, patientNameTest, doctorNameTest, printDateTest, sensorIdTest,
			   continuousAttributesValuesTest, discreteAttributesValuesTest);


		   // Test de r�cup�ration du nom du patient
		   healthPrint1.getPatientName();

           return testResult;
        }
   };

   // Test class for the method getPrintDate of class HealthPrint
   class getPrintDateTest : public THealthPrintMethod
   {
   public:
       getPrintDateTest(THealthPrint* tmp): THealthPrintMethod(tmp) { testResult.name = "getPrintDateTest"; }
       TestResult execute()
        {
		   cout << "Test de r�cup�ration de la date d'un objet HealthPrint" << endl;

		   int idTest;
		   string patientNameTest;
		   string doctorNameTest;
		   string printDateTest;
		   int sensorIdTest;
		   map<string, double> continuousAttributesValuesTest;
		   map<string, string> discreteAttributesValuesTest;

		   // Cr�ation d'un objet HealthPrint avec des param�tres corrects
		   cout << "Saisir un id d'empreinte : ";
		   cin >> idTest;

		   cout << "Saisir un nom de patient : ";
		   cin >> patientNameTest;

		   cout << "Saisir un nom de docteur : ";
		   cin >> doctorNameTest;

		   cout << "Saisir une date de saisie de l'empreinte : ";
		   cin >> printDateTest;

		   cout << "Saisir un id de capteur r�alisant l'empreinte : ";
		   cin >> sensorIdTest;

		   // continuousAttributesValuesTest[nameTest] = matchingRateTest;

		   // discreteAttributesValuesTest[nameTest] = matchingRateTest;

		   HealthPrint healthPrint1(idTest, patientNameTest, doctorNameTest, printDateTest, sensorIdTest,
			   continuousAttributesValuesTest, discreteAttributesValuesTest);


		   // Test de r�cup�ration de la date de l'empreinte
		   healthPrint1.getPrintDate();

           return testResult;
        }
   };

   // Test class for the method analyse of class HealthPrint
   class analyseTest : public THealthPrintMethod
   {
   public:
       analyseTest(THealthPrint* tmp): THealthPrintMethod(tmp) { testResult.name = "analyseTest"; }
       TestResult execute()
        {
		   cout << "Test de la fonction Analyse d'un objet HealthPrint" << endl;

		   int idTest;
		   string patientNameTest;
		   string doctorNameTest;
		   string printDateTest;
		   int sensorIdTest;
		   map<string, double> continuousAttributesValuesTest;
		   map<string, string> discreteAttributesValuesTest;

		   // Cr�ation d'un objet HealthPrint avec des param�tres corrects
		   cout << "Saisir un id d'empreinte : ";
		   cin >> idTest;

		   cout << "Saisir un nom de patient : ";
		   cin >> patientNameTest;

		   cout << "Saisir un nom de docteur : ";
		   cin >> doctorNameTest;

		   cout << "Saisir une date de saisie de l'empreinte : ";
		   cin >> printDateTest;

		   cout << "Saisir un id de capteur r�alisant l'empreinte : ";
		   cin >> sensorIdTest;

		   // continuousAttributesValuesTest[nameTest] = matchingRateTest;

		   // discreteAttributesValuesTest[nameTest] = matchingRateTest;

		   HealthPrint healthPrint1(idTest, patientNameTest, doctorNameTest, printDateTest, sensorIdTest,
			   continuousAttributesValuesTest, discreteAttributesValuesTest);


		   // Test de la focntion Analyse d'un objet HealthPrint


           return testResult;
        }
   };


   // Destructor
    ~THealthPrint() {}
};

#endif //THEALTHPRINT_H
