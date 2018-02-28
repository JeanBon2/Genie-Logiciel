#ifndef ABSTRACTTEST_H
#define ABSTRACTTEST_H

// System include
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

// Personnal include

// Constants

// Types

// Class
class AbstractTest
{
public:
  AbstractTest();

  virtual void beforeClass();
  virtual void afterClass();
  virtual void beforeEachTest();
  virtual void afterEachTest();

  virtual void run();

  ~AbstractTest();

private:
  vector<function<void()>> testsFunctions;

};


#endif //ABSTRACTTEST_H
