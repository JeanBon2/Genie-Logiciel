#ifndef DBMANAGER_H
#define DBMANAGER_H

// System include
#include <iostream>
#include <QSqlDatabase>
using namespace std;

// Personnal include
#include "Disease.h"

// Constants

// Types

// Class
class DbManager
{
	// Attributes
private:
	QSqlDatabase database;

	// Methods
public:
	// Constructors
	DbManager(const string& path);

	// Destructors
	~DbManager();

	// Others
	bool insertIntoDatabase(const vector<Disease>& diseases);

private:
	bool insertIntoDatabase(const Disease& disease);
	bool insertIntoDatabase(const Attribute* attribute);
	bool insertIntoDatabase(const DiscreteAttribute& attribute);
	bool insertIntoDatabase(const ContinuousAttribute& attribute);
	bool insertIntoDatabase(const int diseaseId, const int attributeId);

	void wipeData();
};

#endif // DBMANAGER_H