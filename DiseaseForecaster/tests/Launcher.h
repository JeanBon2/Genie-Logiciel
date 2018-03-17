#ifndef LAUNCHER_H
#define LAUNCHER_H

// System include
#include <iostream>
using namespace std;

// Personnal include
#include "TAnalyse.h"
#include "TAttribute.h"
#include "TDisease.h"
#include "THealthPrint.h"
#include "TPotentialDisease.h"

// Constants

// Types

class Launcher
{
  public:
    void runAllTests()
    {
      TAnalyse tanalyse;
      TAttribute tattribute;
      TDisease tdisease;
      THealthPrinte thealtprint;
      TPotentialDisease tpotentialdisease;

      cout << endl;
      tanalyse.run();
      cout << endl;
      tattribute.run();
      cout << endl;
      tdisease.run();
      cout << endl;
      thealtprint.run();
      cout << endl;
      tpotentialdisease.run();
      cout << endl;
    }

};

#endif //METHODTEST_H
