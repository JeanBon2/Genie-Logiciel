#ifndef TPOTENTIALDISEASE_H
#define TPOTENTIALDISEASE_H

// System include
#include <iostream>
#include <string>
using namespace std;

// Personnal include
#include "c:\Users\asduc.INSA-LYON\Documents\Génie logiciel\Genie-Logiciel\DiseaseForecaster\tests\AbstractTest.h"
#include "c:\Users\asduc.INSA-LYON\Documents\Génie logiciel\Genie-Logiciel\DiseaseForecaster\tests\MethodTest.h"
#include "PotentialDisease.h"

// Constants

// Types
class TPotentialDisease;

class TPotentialDiseaseMethod : public MethodTest
{
public:
    TPotentialDiseaseMethod(TPotentialDisease* tmp)
     :outter(tmp)
     {}
 protected:
     TPotentialDisease* outter;
 };

// Class
class TPotentialDisease : public AbstractTest
{
public:
	int idTest = 1;
	string nameTest = "Coléra";
	double matchingRateTest = 50;
	map<string, double> continuousAttributesValuesTest;
	map<string, string> discreteAttributesValuesTest;

	PotentialDisease potentialD1;

   // Class constructor
   TPotentialDisease()
	   : potentialD1(idTest, nameTest, matchingRateTest, continuousAttributesValuesTest, discreteAttributesValuesTest)
   {
	   continuousAttributesValuesTest.insert(std::pair<string, double>("id", idTest));
	   discreteAttributesValuesTest.insert(std::pair<string, string>("name", nameTest));
	   continuousAttributesValuesTest.insert(std::pair<string, double>("matchingRate", matchingRateTest));
   }

   // This Method add every test method in the run engine
   void init ()
   {
       addTest(new PotentialDiseaseTest(this));
       addTest(new DisplayContentTest(this));
   }

   /*
   Here you can add one event method to handle your tests variables and objects.
    Like beforeEachTest() or afterClass()
   */

   // Test class for the method PotentialDiseaseTest of class PotentialDisease
   class PotentialDiseaseTest : public TPotentialDiseaseMethod
   {
   public:
       PotentialDiseaseTest(TPotentialDisease* tmp): TPotentialDiseaseMethod(tmp) { testResult.name = "PotentialDiseaseTest"; }
       TestResult execute()
        {
		   /*
		   if (! outter->potentialD1)
		   {
		   assert(false);
		   }*/
		   assert(false);

           return testResult;
        }
   };

   // Test class for the method DisplayContentTest of class PotentialDisease
   class DisplayContentTest : public TPotentialDiseaseMethod
   {
   public:
       DisplayContentTest(TPotentialDisease* tmp): TPotentialDiseaseMethod(tmp) { testResult.name = "DisplayContentTest"; }
       TestResult execute()
        {
		   // TODO rediriger le retour vers une variable et non l'écran
		   outter->potentialD1.displayContent();

		   assert(false);

          return testResult;
        }
   };


   // Destructor
    ~TPotentialDisease() {}
};

#endif //TPOTENTIALDISEASE_H
