#ifndef THEALTHPRINT_H
#define THEALTHPRINT_H

// System include
#include <iostream>
#include <string>
using namespace std;

// Personnal include
#include "tests/AbstractTest.h"
#include "tests/MethodTest.h"
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
	   addTest(new getDoctorNameTest(this));
       addTest(new getPrintDateTest(this));
	   addTest(new getContinuousAttributesValuesTest(this));
	   addTest(new getDiscreteAttributesValuesTest(this));
	   addTest(new getIdTest(this));
	   addTest(new getSensorIdTest(this));
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
		   assert(outter->healthPrint1.getId() == outter->idTest);
           assert(outter->healthPrint1.getPatientName().compare(outter->patientNameTest) == 0);
		   assert(outter->healthPrint1.getDoctorName().compare(outter->doctorNameTest) == 0);
           assert(outter->healthPrint1.getPrintDate().toString("dd/MM/yyyy").toStdString().compare(outter->printDateTest) == 0);
		   assert(outter->healthPrint1.getSensorId() == outter->sensorIdTest);
		   assert(outter->healthPrint1.getContinuousAttributesValues() == outter->continuousAttributesValuesTest);
		   assert(outter->healthPrint1.getDiscreteAttributesValues() == outter->discreteAttributesValuesTest);

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
          string message = "";
          string date = "25.04.2016";

        	message += "Sensor ID : " + to_string(int(outter->sensorIdTest)) + "\n";
        	message += "Print date : " + date + "\n"; // .toUtf8().constData()
        	message += "Doctor name : " + outter->doctorNameTest + "\n";
        	message += "Patient name : " + outter->patientNameTest + "\n";

		       string buffer = outter->healthPrint1.displayContent(false);
		       assert(message.compare(buffer) == 0);

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
			     assert(outter->healthPrint1.getPatientName().compare(outter->patientNameTest) == 0);

           return testResult;
        }
   };

   // Test class for the method getDoctorName of class HealthPrint
   class getDoctorNameTest : public THealthPrintMethod
   {
   public:
	   getDoctorNameTest(THealthPrint* tmp) : THealthPrintMethod(tmp) { testResult.name = "getDoctorNameTest"; }
	   TestResult execute()
	   {
		   assert(outter->healthPrint1.getDoctorName().compare(outter->doctorNameTest) == 0);

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
			     assert(outter->healthPrint1.getPrintDate().toString("dd/MM/yyyy").toStdString().compare(outter->printDateTest) == 0);

           return testResult;
        }
   };

   // Test class for the method getContinuousAttributesValues of class HealthPrint
   class getContinuousAttributesValuesTest : public THealthPrintMethod
   {
   public:
	   getContinuousAttributesValuesTest(THealthPrint* tmp) : THealthPrintMethod(tmp) { testResult.name = "getContinuousAttributesValuesTest"; }
	   TestResult execute()
	   {
		   assert(outter->healthPrint1.getContinuousAttributesValues() == outter->continuousAttributesValuesTest);

		   return testResult;
	   }
   };

   // Test class for the method getDiscreteAttributesValues of class HealthPrint
   class getDiscreteAttributesValuesTest : public THealthPrintMethod
   {
   public:
	   getDiscreteAttributesValuesTest(THealthPrint* tmp) : THealthPrintMethod(tmp) { testResult.name = "getDiscreteAttributesValuesTest"; }
	   TestResult execute()
	   {
		   assert(outter->healthPrint1.getDiscreteAttributesValues() == outter->discreteAttributesValuesTest);

		   return testResult;
	   }
   };

   // Test class for the method getId of class HealthPrint
   class getIdTest : public THealthPrintMethod
   {
   public:
	   getIdTest(THealthPrint* tmp) : THealthPrintMethod(tmp) { testResult.name = "getIdTest"; }
	   TestResult execute()
	   {
				assert(outter->healthPrint1.getId() == outter->idTest);

		   return testResult;
	   }
   };

   // Test class for the method getSensorId of class HealthPrint
   class getSensorIdTest : public THealthPrintMethod
   {
   public:
	   getSensorIdTest(THealthPrint* tmp) : THealthPrintMethod(tmp) { testResult.name = "getSensorIdTest"; }
	   TestResult execute()
	   {
		   assert(outter->healthPrint1.getSensorId() == outter->sensorIdTest);

		   return testResult;
	   }
   };

   // Destructor
    ~THealthPrint() {}
};

#endif //THEALTHPRINT_H
