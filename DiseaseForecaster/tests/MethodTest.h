#ifndef METHODTEST_H
#define METHODTEST_H

// System include
#include <iostream>
#include <vector>
using namespace std;

// Personnal include

// Constants

// Types
struct TestResult{
  bool success;
  int testNumber;
  string name;

  TestResult() : success(true), testNumber(0), name("unamed")
  {}
};

class AbstractTest;

// Class
class MethodTest
{
public:

  MethodTest() {}

  virtual TestResult execute() = 0;

  void assert(int expression)
  {
    if (!testResult.success)
      return;

    if (expression == false)
      testResult.success = false;
    else
      testResult.success = true;

    testResult.testNumber++;
  }

  ~MethodTest() {}
protected:
  TestResult testResult;
};


#endif //METHODTEST_H
