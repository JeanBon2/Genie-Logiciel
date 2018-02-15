// System include
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <string>
#include <unordered_map>
using namespace std;

// Personnal include
#include "Interface.h"
#include "MenuInterface.h"
#include "SearchInterface.h"
// Constants
unordered_map <string, string> Interface::texts;
stack<interfaceEnum> Interface::stackInterface;

// Constructors
Interface::Interface()
{
#ifdef DEBUG
	cout << "Interface constructor call" << endl;
#endif // DEBUG
}



// Destructor
Interface::~Interface()
{
#ifdef DEBUG
	cout << "Xxx destructor call" << endl;
#endif // DEBUG
}

// Public methods
bool Interface::loadMap(const string path)	// C'est mieux avec 'Interface::' :P
{
	string key, value;

	QFile languageFile(QString::fromStdString(path));
	cout << path << endl;

	QByteArray byteFile;
	QJsonDocument languageContent;
	QJsonObject dictionnary;

	if (!languageFile.exists())
	{
		//Log.Info();
		return false;
	}
	languageFile.open(QIODevice::ReadOnly);
	byteFile = languageFile.readAll();
	languageContent = QJsonDocument::fromJson(byteFile);
	dictionnary = languageContent.object();
	languageFile.close();

	for (QString& currentKey : dictionnary.keys())
	{
		key = currentKey.toUtf8().constData();
		value = dictionnary.take(currentKey).toString().toUtf8().constData();
		texts.emplace(key, value);
	}

	/*for (auto& test : mapLanguage)
	{
	cout << test.first << ":" << test.second << endl;
	}*/
	return true;
}


// Protected methods
void Interface::previous()
{
	stackInterface.pop();
	createInterface(stackInterface.top());	
}

string Interface::getText(const string keyMessage)
{
	return Interface::texts[keyMessage];
}

void Interface::createInterface(const interfaceEnum interfaceID)
{
	stackInterface.push(interfaceID);
	switch (interfaceID) 
	{
		case MENU_INTERFACE :
			MenuInterface();
			break;

		case SEARCH_INTERFACE:
			SearchInterface();
			break;
		case UPDATE_INTERFACE:
			break;
		case ANALYSE_INTERFACE:
			break;

		default:
			stackInterface.pop();
			return;
	}
}
// Private methods
