#ifndef ABSTRACTTEST_H
#define ABSTRACTTEST_H

// System include
#include <iostream>
#include <vector>
using namespace std;

// Personnal include
#include "MethodTest.h"

// Constants

// Types

// Class
class AbstractTest
{
public:
  AbstractTest();

  /*
    Executed method before all tests
  */
  virtual void beforeClass();

  /*
    Executed method after all tests
  */
  virtual void afterClass();

  /*
    Executed method before each test
  */
  virtual void beforeEachTest();

  /*
    Executed method after each test
  */
  virtual void afterEachTest();

  /*
    In this method, you should use addTest()
    to save all your tests methods.
    Required for the run() method.
  */
  virtual void init() = 0;

  /*
    Execute all tests
  */
  void run();

  /*
    Add a methodTest class in the test launcher
  */
  void addTest(MethodTest *method);

  ~AbstractTest();

protected:
  vector<MethodTest*> testsMethods;

};


#endif //ABSTRACTTEST_H
