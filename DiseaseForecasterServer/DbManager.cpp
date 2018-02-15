// System include
#include <iostream>
#include <string>
using namespace std;

// Personnal include
#include "DbManager.h"

// Constants

// Constructors
DbManager::DbManager(const string& path)
{
#ifdef DEBUG
	cout << "DbManager constructor call" << endl;
#endif // DEBUG
	database = QSqlDatabase::addDatabase("serverDatabase");
	database.setDatabaseName(QString::fromStdString(path));

	if (!database.open())
	{
		// Log
		return;
	}
}

// Destructor
DbManager::~DbManager()
{
#ifdef DEBUG
	cout << "DbManager destructor call" << endl;
#endif // DEBUG
}

// Public methods
bool DbManager::insertIntoDatabase(const vector<Disease>& diseases)
{
	return true;
}