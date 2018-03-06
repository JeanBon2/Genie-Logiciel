#include "TAnalyse.h"
#include "Analyse.h"
#include "HealthPrint.h"
#include "PotentialDisease.h"


TAnalyse::TAnalyse()
{
}


TAnalyse::~TAnalyse()
{
}

void TAnalyse::AnalyseTest()
{
	// Création d'une analyse avec des paramètres corrects
	Analyse analyseCorrects(HealthPrint healthPrint, vector<PotentialDisease> diseases);

	analyseCorrects.DisplayContent();
	
	// Création d'une analyse avec des paramètres erronés
	Analyse analyseEronnes(HealthPrint healthPrint, vector<PotentialDisease> diseases);

	// Création d'une analyse avec des paramètres manquants
	Analyse analyseManquants(HealthPrint healthPrint);
}

void TAnalyse::displayContentTest()
{
	// Demande d'affichage d'une analyse correcte

	// Demande d'affichage d'une analyse corrompue

	// Demande d'affichage d'una analyse manquante

}

void TAnalyse::displayHeaderTest()
{
	// Demande d'affichage d'une analyse correcte

	// Demande d'affichage d'une analyse corrompue

	// Demande d'affichage d'una analyse manquante

}
