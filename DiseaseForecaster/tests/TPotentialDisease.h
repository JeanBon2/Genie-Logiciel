#ifndef TPOTENTIALDISEASE_H
#define TPOTENTIALDISEASE_H

// System include
#include <iostream>
#include <string>
#include <map>
using namespace std;

// Personnal include
#include "tests/AbstractTest.h"
#include "tests/MethodTest.h"
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
	string nameTest = "Col�ra";
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
	   addTest(new getIdTest(this));
	   addTest(new getContinuousAttributesValuesTest(this));
	   addTest(new getDiscreteAttributesValuesTest(this));
	   addTest(new getNameTest(this));
	   addTest(new getMatchingRateTest(this));
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
		   map<string, double> retour;
		   retour = outter->potentialD1.getContinuousAttributesValues();
		   map<string, string> retour2;
		   retour2 = outter->potentialD1.getDiscreteAttributesValues();

		   assert(outter->potentialD1.getId() == outter->idTest);
		   assert(outter->potentialD1.getName().compare(outter->nameTest) == 0);
		   assert(outter->potentialD1.getMatchingRate() == outter->matchingRateTest);
		   for (auto&& iterateur : retour)
		   {
			   assert(iterateur.second == outter->continuousAttributesValuesTest[iterateur.first]);
		   }
		   for (auto&& iterateur : retour2)
		   {
			   assert(iterateur.second == outter->discreteAttributesValuesTest[iterateur.first]);
		   }

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
		   string message = "";

		   message += "Disease name : " + outter->nameTest + "\n";
		   message += "Matching rate : " + to_string(outter->matchingRateTest) + "\n";;
		   for (auto const& continuousAttributeValue : outter->continuousAttributesValuesTest)
		   {
			   message += continuousAttributeValue.first + " " + to_string(continuousAttributeValue.second) + "\n";
		   }
		   for (auto const& discreteAttributesValue : outter->discreteAttributesValuesTest)
		   {
			   message += discreteAttributesValue.first + " " + discreteAttributesValue.second + "\n";
		   }

		   string buffer = outter->potentialD1.displayContent(false);
		   assert(message.compare(buffer) == 0);

          return testResult;
        }
   };

   // Test class for the method getId of class PotentialDisease
   class getIdTest : public TPotentialDiseaseMethod
   {
   public:
	   getIdTest(TPotentialDisease* tmp) : TPotentialDiseaseMethod(tmp) { testResult.name = "getIdTestTest"; }
	   TestResult execute()
	   {
		   assert(outter->potentialD1.getId() == outter->idTest);

		   return testResult;
	   }
   };

   // Test class for the method getContinuousAttributesValues of class PotentialDisease
   class getContinuousAttributesValuesTest : public TPotentialDiseaseMethod
   {
   public:
	   getContinuousAttributesValuesTest(TPotentialDisease* tmp) : TPotentialDiseaseMethod(tmp) { testResult.name = "getContinuousAttributesValuesTest"; }
	   TestResult execute()
	   {
		   map<string, double> retour;
		   retour = outter->potentialD1.getContinuousAttributesValues();

		   for (auto&& iterateur : retour)
		   {
			   assert(iterateur.second == outter->continuousAttributesValuesTest[iterateur.first]);
		   }

		   return testResult;
	   }
   };

   // Test class for the method getDiscreteAttributesValues of class PotentialDisease
   class getDiscreteAttributesValuesTest : public TPotentialDiseaseMethod
   {
   public:
	   getDiscreteAttributesValuesTest(TPotentialDisease* tmp) : TPotentialDiseaseMethod(tmp) { testResult.name = "getDiscreteAttributesValuesTest"; }
	   TestResult execute()
	   {
		   map<string, string> retour;
		   retour = outter->potentialD1.getDiscreteAttributesValues();

		   for (auto&& iterateur : retour)
		   {
			   assert(iterateur.second == outter->discreteAttributesValuesTest[iterateur.first]);
		   }

		   return testResult;
	   }
   };

   // Test class for the method getName of class PotentialDisease
   class getNameTest : public TPotentialDiseaseMethod
   {
   public:
	   getNameTest(TPotentialDisease* tmp) : TPotentialDiseaseMethod(tmp) { testResult.name = "getNameTest"; }
	   TestResult execute()
	   {
		   assert(outter->potentialD1.getName().compare(outter->nameTest) == 0);

		   return testResult;
	   }
   };

   // Test class for the method getMatchingRate of class PotentialDisease
   class getMatchingRateTest : public TPotentialDiseaseMethod
   {
   public:
	   getMatchingRateTest(TPotentialDisease* tmp) : TPotentialDiseaseMethod(tmp) { testResult.name = "getMatchingRateTest"; }
	   TestResult execute()
	   {
		   assert(outter->potentialD1.getMatchingRate() == outter->matchingRateTest);

		   return testResult;
	   }
   };


   // Destructor
    ~TPotentialDisease() {}
};

#endif //TPOTENTIALDISEASE_H
