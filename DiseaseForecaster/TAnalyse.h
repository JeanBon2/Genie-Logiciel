#ifndef TANALYSE_H
#define TANALYSE_H

// System include
#include <iostream>
using namespace std;

// Personnal include
#include "c:\Users\asduc.INSA-LYON\Documents\Génie logiciel\Genie-Logiciel\DiseaseForecaster\tests\AbstractTest.h"
#include "c:\Users\asduc.INSA-LYON\Documents\Génie logiciel\Genie-Logiciel\DiseaseForecaster\tests\MethodTest.h"
#include "Analyse.h"

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
   // Class constructor
   TAnalyse() {}

   // This Method add every test method in the run engine
   void init ()
   {
       addTest(new AnalyseTest(this));
       addTest(new displayContentTest(this));
       addTest(new displayHeaderTest(this));
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
		   cout << "Test de création d'un objet Analyse" << endl;

		   HealthPrint healthPrintTest(/*Paramètes corrects*/);
		   vector<PotentialDisease> diseasesTest(/*Paramètes corrects*/);
		   int idTest;

		   // Test de création d'un objet Analyse avec des paramètres corrects
		   cout << "Saisir un id d'analyse : ";
		   cin >> idTest;

		   Analyse analyse1(idTest, healthPrintTest, diseasesTest);


		   // Test de création d'un objet Analyse avec un id existant
		   cout << "Saisir un id d'analyse existant : ";
		   cin >> idTest;

		   Analyse analyse2(idTest, healthPrintTest, diseasesTest);

		   // Test de création d'un objet Analyse avec un id incorrect
		   cout << "Saisir un id d'analyse incorrect : ";
		   cin >> idTest;

		   Analyse analyse3(idTest, healthPrintTest, diseasesTest);
          return testResult;
        }
   };

   // Test class for the method displayContent of class Analyse
   class displayContentTest : public TAnalyseMethod
   {
   public:
       displayContentTest(TAnalyse* tmp): TAnalyseMethod(tmp) { testResult.name = "displayContentTest"; }
       TestResult execute()
        {
		   cout << "Test d'affichage du contenu d'un objet Analyse" << endl;
		   // Demande d'affichage d'une analyse correcte

		   // Demande d'affichage d'une analyse corrompue

		   // Demande d'affichage d'una analyse manquante

          return testResult;
        }
   };

   // Test class for the method displayHeader of class Analyse
   class displayHeaderTest : public TAnalyseMethod
   {
   public:
       displayHeaderTest(TAnalyse* tmp): TAnalyseMethod(tmp) { testResult.name = "displayHeaderTest"; }
       TestResult execute()
        {
		   cout << "Test d'affichage de l'en-tête d'un objet Analyse" << endl;
		   // Demande d'affichage d'une analyse correcte

		   // Demande d'affichage d'une analyse corrompue

		   // Demande d'affichage d'una analyse manquante

          return testResult;
        }
   };


   // Destructor
    ~TAnalyse() {}
};

#endif //TANALYSE_H
