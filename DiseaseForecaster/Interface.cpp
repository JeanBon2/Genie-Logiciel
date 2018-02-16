// System include
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <string>
#include <unordered_map>
#include <iterator>
using namespace std;

// Personnal include
#include "Interface.h"
#include "MenuInterface.h"
#include "SearchInterface.h"
#include "Log.h"
// Constants
unordered_map <string, string> Interface::texts;
stack<Interface::interfaceList> Interface::stackInterface;

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
	const QString defaultpath = R"(.\Language\Fr_fr.lng)";
	string key, value;
	QFile languageFile(QString::fromStdString(path));

	QByteArray byteFile;
	QJsonDocument languageContent;
	QJsonObject dictionnary;

	if (!languageFile.exists())
	{
		languageFile.setFileName(defaultpath);
		if (!languageFile.exists())
		{
			cout << "Can't access to default language" << endl << endl;
			return false;
		}
		
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
void Interface::start()
{
	createInterface(MENU_INTERFACE);
}


// Protected methods
void Interface::previous()
{
	stackInterface.pop();
	createInterface(stackInterface.top());	
}

string Interface::getText(const string keyMessage)
{
	unordered_map< string, string>:: const_iterator  valueMessage = Interface::texts.find(keyMessage);
	if (valueMessage != texts.end())
	{
		return valueMessage->second;
	}
	else
	{
		Log::info("Not able to found : \""+ keyMessage + "\" in languageFile");
		return "No Message Found";
	}
}

void Interface::createInterface(const interfaceList interfaceID)
{
	Interface* currentInterface;
	stackInterface.push(interfaceID);
	switch (interfaceID) 
	{
		case MENU_INTERFACE :
			currentInterface= new MenuInterface();
			break;

		case SEARCH_INTERFACE:
			currentInterface = new SearchInterface();
			break;

		case UPDATE_INTERFACE:
			break;

		case ANALYSE_INTERFACE:
			break;

		default:
			stackInterface.pop();
			return;
	}
	currentInterface->run();
	delete currentInterface;
}

string Interface::getAction()
{
	string inputValue;
	getline(cin, inputValue);

	return inputValue;
}
// Private methods
