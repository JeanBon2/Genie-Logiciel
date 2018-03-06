#ifndef TATTRIBUTE_H
#define TATTRIBUTE_H

// System include
#include <iostream>
using namespace std;

// Personnal include
#include "AbstractTest.h"
#include "MethodTest.h"
#include "Attribute.h"

// Constants

// Types
class TAttribute;

class TAttributeMethod : public MethodTest
{
public:
    TAttributeMethod(TAttribute* tmp)
     :outter(tmp)
     {}
 protected:
     TAttribute* outter;
 };

// Class
class TAttribute : public AbstractTest
{
public:
   // Class constructor
   TAttribute() {}

   // This Method add every test method in the run engine
   void init ()
   {
       addTest(new AttributeTest(this));
       addTest(new getIdTest(this));
       addTest(new getNameTest(this));
       addTest(new isDiscreteTest(this));
   }

   /*
   Here you can add one event method to handle your tests variables and objects.
    Like beforeEachTest() or afterClass()
   */

   // Test class for the method Attribute of class Attribute
   class AttributeTest : public TAttributeMethod
   {
   public:
       AttributeTest(TAttribute* tmp): TAttributeMethod(tmp) { testResult.name = "AttributeTest"; }
       TestResult execute()
        {
          return testResult;
        }
   };

   // Test class for the method getId of class Attribute
   class getIdTest : public TAttributeMethod
   {
   public:
       getIdTest(TAttribute* tmp): TAttributeMethod(tmp) { testResult.name = "getIdTest"; }
       TestResult execute()
        {
          return testResult;
        }
   };

   // Test class for the method getName of class Attribute
   class getNameTest : public TAttributeMethod
   {
   public:
       getNameTest(TAttribute* tmp): TAttributeMethod(tmp) { testResult.name = "getNameTest"; }
       TestResult execute()
        {
          return testResult;
        }
   };

   // Test class for the method isDiscrete of class Attribute
   class isDiscreteTest : public TAttributeMethod
   {
   public:
       isDiscreteTest(TAttribute* tmp): TAttributeMethod(tmp) { testResult.name = "isDiscreteTest"; }
       TestResult execute()
        {
          return testResult;
        }
   };


   // Destructor
    ~TAttribute() {}
};

#endif //TATTRIBUTE_H
