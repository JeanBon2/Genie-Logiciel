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
	double idTest = 1;
	string patientNameTest = "Dupont";
	string doctorNameTest = "Durand";
	string printDateTest = "25/04/2016";
	double sensorIdTest = 1;
	map<string, double> continuousAttributesValuesTest;
	map<string, string> discreteAttributesValuesTest;
	HealthPrint healthPrint1;

   // Class constructor
   THealthPrint()
	   : healthPrint1(idTest, patientNameTest, doctorNameTest, printDateTest,
		   sensorIdTest, continuousAttributesValuesTest, discreteAttributesValuesTest)
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
		   /*
		   if (! outter->healthPrint1)
		   {
			   assert(false);
		   }*/
		   assert(false);
		   
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
		   // TODO rediriger l'affichage vers une variable afin
		   outter->healthPrint1.displayContent();

		   assert(false);
		   
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
		   string patientNameRetour;

		   // Test de récupération du nom du patient
		   patientNameRetour = outter->healthPrint1.getPatientName();

		   if (outter->patientNameTest != patientNameRetour)
		   {
			   assert(false);
		   }

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
		   QDate dateRetour;
		   string dateR;

		   // Test de récupération de la date de l'empreinte
		   dateRetour = outter->healthPrint1.getPrintDate();
		   dateR = dateRetour.toString("dd.MM.yyyy").toUtf8().constData();

		   if (dateR != outter->printDateTest)
		   {
			   assert(false);
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
		   //outter->healthPrint1.analyse();
		   
		   assert(false);
		   
           return testResult;
        }
   };


   // Destructor
    ~THealthPrint() {}
};

#endif //THEALTHPRINT_H
