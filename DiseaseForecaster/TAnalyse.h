#ifndef TANALYSE_H
#define TANALYSE_H

// System include
#include <iostream>
using namespace std;

// Personnal include
#include "c:\Users\asduc.INSA-LYON\Documents\Génie logiciel\Genie-Logiciel\DiseaseForecaster\tests\AbstractTest.h"
#include "c:\Users\asduc.INSA-LYON\Documents\Génie logiciel\Genie-Logiciel\DiseaseForecaster\tests\MethodTest.h"
#include "Analyse.h"

// Constants

// Types
class TAnalyse;

class TAnalyseMethod : public MethodTest
{
public:
    TAnalyseMethod(TAnalyse* tmp)
     :outter(tmp)
     {}
 protected:
     TAnalyse* outter;
 };

// Class
class TAnalyse : public AbstractTest
{
public:
   // Class constructor
   TAnalyse() {}

   // This Method add every test method in the run engine
   void init ()
   {
       addTest(new AnalyseTest(this));
       addTest(new displayContentTest(this));
       addTest(new displayHeaderTest(this));
   }

   /*
   Here you can add one event method to handle your tests variables and objects.
    Like beforeEachTest() or afterClass()
   */

   // Test class for the method Analyse of class Analyse
   class AnalyseTest : public TAnalyseMethod
   {
   public:
       AnalyseTest(TAnalyse* tmp): TAnalyseMethod(tmp) { testResult.name = "AnalyseTest"; }
       TestResult execute()
        {
          return testResult;
        }
   };

   // Test class for the method displayContent of class Analyse
   class displayContentTest : public TAnalyseMethod
   {
   public:
       displayContentTest(TAnalyse* tmp): TAnalyseMethod(tmp) { testResult.name = "displayContentTest"; }
       TestResult execute()
        {
          return testResult;
        }
   };

   // Test class for the method displayHeader of class Analyse
   class displayHeaderTest : public TAnalyseMethod
   {
   public:
       displayHeaderTest(TAnalyse* tmp): TAnalyseMethod(tmp) { testResult.name = "displayHeaderTest"; }
       TestResult execute()
        {
          return testResult;
        }
   };


   // Destructor
    ~TAnalyse() {}
};

#endif //TANALYSE_H
