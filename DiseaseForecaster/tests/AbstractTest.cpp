#include "AbstractTest.h"


void AbstractTest::beforeClass()
{

}

void AbstractTest::afterClass()
{

}

void AbstractTest::beforeEachTest()
{

}

void AbstractTest::afterEachTest()
{

}

void AbstractTest::run()
{

}

AbstractTest::AbstractTest()
{
  #ifdef DEBUG
  	cout << "AbstractTest constructor call" << endl;
  #endif // DEBUG

  //testsFunctions = new vector<function<void()>>();
}

AbstractTest::~AbstractTest()
{
  #ifdef DEBUG
  	cout << "AbstractTest constructor call" << endl;
  #endif // DEBUG
}
