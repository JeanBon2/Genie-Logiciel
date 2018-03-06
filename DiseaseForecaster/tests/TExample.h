#ifndef TEXAMPLE_H
#define TEXAMPLE_H

// System include
#include <iostream>
using namespace std;

// Personnal include
#include "AbstractTest.h"
#include "MethodTest.h"

// Constants

// Types
class TExample;

class TExampleMethod : public MethodTest
{
public:
  TExampleMethod(TExample* tmp)
  :outter(tmp)
  {}
protected:
  TExample* outter;
};

// Class
class TExample : public AbstractTest
{
public:
  int a, b, c, d;

  TExample() {}

  void init ()
  {
    addTest(new ExampleTest1(this));
    addTest(new ExampleTest2(this));
    addTest(new ExampleTest3(this));
  }

  void beforeEachTest()
  {
    a = 10;
    b = a + 56;
    c = -10;
    d = 78039499;
  }

  // TODO Accèder aux attributs de la classe, héritage ?
  // TODO Renvoyer le nom de la classe au run pour un aperçu des résultats des tests

  class ExampleTest1 : public TExampleMethod
  {
  public:
    ExampleTest1(TExample* tmp): TExampleMethod(tmp) { testResult.name = "ExampleTest1"; }

    TestResult execute()
    {
      assert(outter->a == 10);
      assert(outter->c == -10);
      assert(outter->b == 60);
      return testResult;
    }
  };

  class ExampleTest2 : public TExampleMethod
  {
  public:
    ExampleTest2(TExample* tmp): TExampleMethod(tmp) { testResult.name = "ExampleTest2"; }

    TestResult execute()
    {
      return testResult;
    }
  };

  class ExampleTest3 : public TExampleMethod
  {
  public:
    ExampleTest3(TExample* tmp): TExampleMethod(tmp) { testResult.name = "ExampleTest3"; }

    TestResult execute()
    {
      return testResult;
    }
  };

  ~TExample() {}
};


#endif //TEXAMPLE_H
