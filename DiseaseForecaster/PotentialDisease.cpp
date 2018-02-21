// System include
using namespace std;
#include <iostream>
#include <string>
#include <map>

// Personnal include
#include "PotentialDisease.h"

// Constructors
PotentialDisease::PotentialDisease(string name, double matchingRate, map<string, double> attributes) : name(name), matchingRate(matchingRate), attributes(attributes)
{
	#ifdef DEBUG
		cout << "PotentialDisease constructor call" << endl;
	#endif // DEBUG
}

// Destructor
PotentialDisease::~PotentialDisease()
{
	#ifdef DEBUG
		cout << "PotentialDisease destructor call" << endl;
	#endif // DEBUG
}
//Others
void PotentialDisease::displayContent()
{
	cout <<"Disease name : "<< name << endl;
	cout <<"Matching rate : " << matchingRate<< endl;
	for (auto const& attribute : attributes)
	{
		cout << attribute.first << " "<< attribute.second << endl;
	}
}