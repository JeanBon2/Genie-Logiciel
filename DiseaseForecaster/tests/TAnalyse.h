#ifndef TANALYSE_H
#define TANALYSE_H

// System include
#include <iostream>
using namespace std;

// Personnal include
#include "AbstractTest.h"
#include "MethodTest.h"
#include "../Analyse.h"
#include "../PotentialDisease.h"

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

  Analyse a1, a2;
  HealthPrint hp1;
  vector<PotentialDisease> diseases;

   // Class constructor
   TAnalyse()
   : hp1(156, "John", "Kevin", "19/08/2017", 5674)
   , a1(1, hp1, diseases)
   , a2(2, hp1)
   {}

   // This Method add every test method in the run engine
   void init ()
   {
       addTest(new AnalyseTest(this));
       addTest(new DisplayContentTest(this));
       addTest(new DisplayHeaderTest(this));
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
          assert(outter->a1.getId() == 1);
          assert(outter->a1.getHealthprint().getId() == 156);

          assert(outter->a2.getId() == 2);
          assert(outter->a2.getHealthprint().getId() == 156);

          return testResult;
        }
   };

   // Test class for the method DisplayContent of class Analyse
   class DisplayContentTest : public TAnalyseMethod
   {
   public:
       DisplayContentTest(TAnalyse* tmp): TAnalyseMethod(tmp) { testResult.name = "DisplayContentTest"; }
       TestResult execute()
        {
          return testResult;
        }
   };

   // Test class for the method DisplayHeader of class Analyse
   class DisplayHeaderTest : public TAnalyseMethod
   {
   public:
       DisplayHeaderTest(TAnalyse* tmp): TAnalyseMethod(tmp) { testResult.name = "DisplayHeaderTest"; }
       TestResult execute()
        {
          return testResult;
        }
   };


   // Destructor
    ~TAnalyse() {}
};

#endif //TANALYSE_H
