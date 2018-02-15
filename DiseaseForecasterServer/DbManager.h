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
};

#endif // DBMANAGER_H