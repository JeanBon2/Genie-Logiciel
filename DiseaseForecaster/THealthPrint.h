#ifndef THEALTHPRINT_H
#define THEALTHPRINT_H

// System include
#include <iostream>
using namespace std;

// Personnal include
#include "c:\Users\asduc.INSA-LYON\Documents\Génie logiciel\Genie-Logiciel\DiseaseForecaster\tests\AbstractTest.h"
#include "c:\Users\asduc.INSA-LYON\Documents\Génie logiciel\Genie-Logiciel\DiseaseForecaster\tests\MethodTest.h"
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
   THealthPrint() 
   {
	   // Création d'un objet HealthPrint avec des paramètres corrects
	   continuousAttributesValuesTest.insert(std::pair<string, double>("id", idTest));
	   discreteAttributesValuesTest.insert(std::pair<string, string>("patientName", patientNameTest));
	   discreteAttributesValuesTest.insert(std::pair<string, string>("doctorName", doctorNameTest));
	   discreteAttributesValuesTest.insert(std::pair<string, string>("printDate", printDateTest));
	   continuousAttributesValuesTest.insert(std::pair<string, double>("sensorId", sensorIdTest));
   }

   // This Method add every test method in the run engine
   void init ()
   {
       addTest(new HealthPrintTest(this));
       addTest(new displayContentTest(this));
       addTest(new getPatientNameTest(this));
       addTest(new getPrintDateTest(this));
       addTest(new analyseTest(this));
   }

   double idTest = 1;
   string patientNameTest = "Dupont";
   string doctorNameTest = "Durand";
   string printDateTest = "25/04/2016";
   double sensorIdTest = 1;
   map<string, double> continuousAttributesValuesTest;
   map<string, string> discreteAttributesValuesTest;

   QDate dateRetour;
   string dateR;


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
		   cout << "Test de création d'un objet HealthPrint" << endl;

		   HealthPrint healthPrint1(idTest, patientNameTest, doctorNameTest, printDateTest, sensorIdTest,
			   continuousAttributesValuesTest, discreteAttributesValuesTest);

		   if (healthPrint1 != nullptr)
		   {
			   testResult.success = true;
		   }
		   else
		   {
			   testResult.success = false;
		   }
		   
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

		   // Création d'un objet HealthPrint avec des paramètres corrects
		   cout << "Saisir un id d'empreinte : ";
		   cin >> idTest;

		   cout << "Saisir un nom de patient : ";
		   cin >> patientNameTest;

		   cout << "Saisir un nom de docteur : ";
		   cin >> doctorNameTest;

		   cout << "Saisir une date de saisie de l'empreinte : ";
		   cin >> printDateTest;

		   cout << "Saisir un id de capteur réalisant l'empreinte : ";
		   cin >> sensorIdTest;

		   // continuousAttributesValuesTest[nameTest] = matchingRateTest;

		   // discreteAttributesValuesTest[nameTest] = matchingRateTest;

		   HealthPrint healthPrint1(idTest, patientNameTest, doctorNameTest, printDateTest, sensorIdTest,
			   continuousAttributesValuesTest, discreteAttributesValuesTest);



		   // Création d'un objet HealthPrint avec un id d'empreinte déjà existant
		   cout << "Saisir un id d'empreinte existant : ";
		   cin >> idTest;

		   cout << "Saisir un nom de patient : ";
		   cin >> patientNameTest;

		   cout << "Saisir un nom de docteur : ";
		   cin >> doctorNameTest;

		   cout << "Saisir une date de saisie de l'empreinte : ";
		   cin >> printDateTest;

		   cout << "Saisir un id de capteur réalisant l'empreinte : ";
		   cin >> sensorIdTest;

		   // continuousAttributesValuesTest[nameTest] = matchingRateTest;

		   // discreteAttributesValuesTest[nameTest] = matchingRateTest;

		   HealthPrint healthPrint2(idTest, patientNameTest, doctorNameTest, printDateTest, sensorIdTest,
			   continuousAttributesValuesTest, discreteAttributesValuesTest);


		   // Test d'affichage d'un objet HealthPrint avec des paramètres corrects
		   healthPrint1.displayContent();

		   // Test d'affichage d'un objet HealthPrint avec des apramètres incorrects
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
		   cout << "Test de récupération du nom du patient d'un objet HealthPrint" << endl;

		   int idTest;
		   string patientNameTest;
		   string doctorNameTest;
		   string printDateTest;
		   int sensorIdTest;
		   map<string, double> continuousAttributesValuesTest;
		   map<string, string> discreteAttributesValuesTest;

		   // Création d'un objet HealthPrint avec des paramètres corrects
		   cout << "Saisir un id d'empreinte : ";
		   cin >> idTest;

		   cout << "Saisir un nom de patient : ";
		   cin >> patientNameTest;

		   cout << "Saisir un nom de docteur : ";
		   cin >> doctorNameTest;

		   cout << "Saisir une date de saisie de l'empreinte : ";
		   cin >> printDateTest;

		   cout << "Saisir un id de capteur réalisant l'empreinte : ";
		   cin >> sensorIdTest;

		   // continuousAttributesValuesTest[nameTest] = matchingRateTest;

		   // discreteAttributesValuesTest[nameTest] = matchingRateTest;

		   HealthPrint healthPrint1(idTest, patientNameTest, doctorNameTest, printDateTest, sensorIdTest,
			   continuousAttributesValuesTest, discreteAttributesValuesTest);


		   // Test de récupération du nom du patient
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
		   cout << "Test de récupération de la date d'un objet HealthPrint" << endl;

		   double idTest;
		   string patientNameTest;
		   string doctorNameTest;
		   string printDateTest;
		   double sensorIdTest;
		   map<string, double> continuousAttributesValuesTest;
		   map<string, string> discreteAttributesValuesTest;

		   QDate dateRetour;
		   string dateR;

		   // Création d'un objet HealthPrint avec des paramètres corrects
		   idTest = 1;

		   patientNameTest = "Dupont";

		   doctorNameTest = "Durand";

		   printDateTest = "25/04/2016";

		   sensorIdTest = 1;

		   continuousAttributesValuesTest.insert(std::pair<string, double>("id", idTest));
		   discreteAttributesValuesTest.insert(std::pair<string, string>("patientName", patientNameTest));
		   discreteAttributesValuesTest.insert(std::pair<string, string>("doctorName", doctorNameTest));
		   discreteAttributesValuesTest.insert(std::pair<string, string>("printDate", printDateTest));
		   continuousAttributesValuesTest.insert(std::pair<string, double>("sensorId", sensorIdTest));


		   HealthPrint healthPrint1(idTest, patientNameTest, doctorNameTest, printDateTest, sensorIdTest,
			   continuousAttributesValuesTest, discreteAttributesValuesTest);


		   // Test de récupération de la date de l'empreinte
		   dateRetour = healthPrint1.getPrintDate();
		   dateR = dateRetour.toString("dd.MM.yyyy").toUtf8().constData();

		   if (dateR == printDateTest)
		   {
			   testResult.success = true;
		   }
		   else
		   {
			   testResult.success = false;
		   }

		   

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

		   // Création d'un objet HealthPrint avec des paramètres corrects
		   idTest = 1;

		   patientNameTest = "Dupont";

		   doctorNameTest = "Durand";

		   printDateTest = "25/04/2016";

		   sensorIdTest = 1;

		   // continuousAttributesValuesTest[nameTest] = matchingRateTest;

		   // discreteAttributesValuesTest[nameTest] = matchingRateTest;

		   HealthPrint healthPrint1(idTest, patientNameTest, doctorNameTest, printDateTest, sensorIdTest,
			   continuousAttributesValuesTest, discreteAttributesValuesTest);

		   // TODO rediriger l'affichage vers une variable afin
		   healthPrint1.displayContent();

           return testResult;
        }
   };


   // Destructor
    ~THealthPrint() {}
};

#endif //THEALTHPRINT_H
