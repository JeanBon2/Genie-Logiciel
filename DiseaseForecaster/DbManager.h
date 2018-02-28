#ifndef DBMANAGER_H
#define DBMANAGER_H

// System include
#include <QSqlDatabase>
using namespace std;

// Personnal include
#include "Analyse.h"

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
	bool insertIntoDatabase(const Analyse& analyse);
	bool insertIntoDatabase(const vector<Analyse>& diseases);
	vector<Analyse> getAnalyseResults();
	
	void wipeData();

private:

};

#endif // DBMANAGER_H
