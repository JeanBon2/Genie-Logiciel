#include "AbstractTest.h"

void AbstractTest::beforeClass()
{
  #ifdef DEBUG
    cout << "beforeClass" << endl;
  #endif // DEBUG
}

void AbstractTest::afterClass()
{
  #ifdef DEBUG
    cout << "afterClass" << endl;
  #endif // DEBUG
}

void AbstractTest::beforeEachTest()
{
  #ifdef DEBUG
    cout << "beforeEachTest" << endl;
  #endif // DEBUG
}

void AbstractTest::afterEachTest()
{
  #ifdef DEBUG
    cout << "afterEachClass" << endl;
  #endif // DEBUG
}

void AbstractTest::run()
{
  init();

  beforeClass();

  for(auto&& met : testsMethods)
  {
    beforeEachTest();

    TestResult testResult = met->execute();

    cout << testResult.name << " ";;
    if (testResult.success)
      cout << "succès." << endl;
    else
      cout << "echec au " << testResult.testNumber << " test." << endl;

    afterEachTest();
  }

  afterClass();
}

void AbstractTest::addTest(MethodTest *method)
{
  testsMethods.push_back(method);
}

AbstractTest::AbstractTest()
{
  #ifdef DEBUG
  	cout << "AbstractTest constructor call" << endl;
  #endif // DEBUG
}

AbstractTest::~AbstractTest()
{
  #ifdef DEBUG
  	cout << "AbstractTest constructor call" << endl;
  #endif // DEBUG
}
