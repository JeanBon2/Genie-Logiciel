#ifndef TDISEASE_H
#define TDISEASE_H

// System include
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Personnal include
#include "AbstractTest.h"
#include "MethodTest.h"
#include "../Disease.h"

// Constants

// Types
class TDisease;

class TDiseaseMethod : public MethodTest
{
public:
  TDiseaseMethod(TDisease* tmp)
  : outter(tmp)
  {}
protected:
  TDisease* outter;
};

// Class
class TDisease : public AbstractTest
{
public:

  void init ()
  {
    addTest(new DiseaseTest(this));
    addTest(new getIdTest(this));
    addTest(new getNameTest(this));
    addTest(new getDiscriminantAttributesTest(this));
    addTest(new addDiscriminantAttributeTest(this));
    addTest(new isDiscriminantTest(this));
  }

  //
  Disease d1;
  Disease d2;
  string name1 = "Ebola", name2 = "VIH";
  shared_ptr<Attribute> attribute1, attribute2, attribute3;
  vector<shared_ptr<Attribute>> attributes;

  TDisease()
  :
  d1(0, "Ebola"), // TODO Set attributes
  d2(1, "VIH"),
  attribute1(new Attribute(0, "Attribute1", false)),
  attribute2(new Attribute(1, "Attribute2", false)),
  attribute3(new Attribute(2, "Attribute3", false))
  {
    attributes.push_back(attribute1);
    attributes.push_back(attribute2);
    attributes.push_back(attribute3);
  }

  // Begin of tests methods
  class DiseaseTest : public TDiseaseMethod
  {
  public:
    DiseaseTest(TDisease* tmp): TDiseaseMethod(tmp) { testResult.name = "DiseaseTest"; }

    TestResult execute()
    {
      assert(outter->d1.getId() == 0);
      assert(outter->d1.getName().compare(outter->name1) == 0);

      assert(outter->d2.getId() == 1);
      assert(outter->d2.getName().compare(outter->name2) == 0);

      return testResult;
    }
  };

  class getIdTest : public TDiseaseMethod
  {
  public:
    getIdTest(TDisease* tmp): TDiseaseMethod(tmp) { testResult.name = "getIdTest"; }

    TestResult execute()
    {
      assert(outter->d1.getId() == 0);
      assert(outter->d2.getId() == 1);

      return testResult;
    }
  };

  class getNameTest : public TDiseaseMethod
  {
  public:
    getNameTest(TDisease* tmp): TDiseaseMethod(tmp) { testResult.name = "getNameTest"; }

    TestResult execute()
    {
      assert(outter->d1.getName().compare(outter->name1) == 0);
      assert(outter->d2.getName().compare(outter->name2) == 0);

      outter->d1.addDiscriminantAttribute(outter->attributes[0]);
      outter->d1.addDiscriminantAttribute(outter->attributes[1]);
      outter->d1.addDiscriminantAttribute(outter->attributes[2]);

      return testResult;
    }
  };

  class getDiscriminantAttributesTest : public TDiseaseMethod
  {
  public:
    getDiscriminantAttributesTest(TDisease* tmp): TDiseaseMethod(tmp) { testResult.name = "getDiscriminantAttributesTest"; }

    TestResult execute()
    {
      vector<shared_ptr<Attribute>> attributes = outter->d1.getDiscriminantAttributes();

      assert(attributes[0]->getId() == outter->attributes[0]->getId());
      assert(attributes[2]->getId() == outter->attributes[2]->getId());

      return testResult;
    }
  };

  class addDiscriminantAttributeTest : public TDiseaseMethod
  {
  public:
    addDiscriminantAttributeTest(TDisease* tmp): TDiseaseMethod(tmp) { testResult.name = "addDiscriminantTest"; }

    TestResult execute()
    {
      vector<shared_ptr<Attribute>> attributes = outter->d1.getDiscriminantAttributes();

      assert(attributes[0]->getId() == outter->attributes[0]->getId());
      assert(attributes[1]->getId() == outter->attributes[1]->getId());

      return testResult;
    }
  };

  class isDiscriminantTest : public TDiseaseMethod
  {
  public:
    isDiscriminantTest(TDisease* tmp): TDiseaseMethod(tmp) { testResult.name = "isDiscriminantTest"; }

    TestResult execute()
    {
      shared_ptr<Attribute> newAttribute = make_shared<Attribute>(Attribute(3, "Attribute4", false));
      assert(outter->d1.isDiscriminant(outter->attributes[1]) == true);
      assert(outter->d1.isDiscriminant(newAttribute) == false);

      return testResult;
    }
  };

  ~TDisease() {}
};

#endif //TDISEASE
