// System include
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QFile>
#include <string>
#include <map>
using namespace std;

// Personnal include
#include "Interface.h"
// Constants
map<string, string> Interface::mapLanguage;

// Constructors
Interface::Interface()
{
#ifdef DEBUG
	cout << "Interface constructor call" << endl;
#endif // DEBUG
}

Interface::Interface(const Interface* x)
{
#ifdef DEBUG
	cout << "Interface copy constructor call" << endl;
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


// Protected methods
void Interface::previous()
{

}

string Interface::getText(const string keyMessage)
{
	return "";
}


void Interface::getInterfaceText()
{

}

string Interface::getAction()
{
	return "";
}

void Interface::createInterface(const int interfaceID)
{
	switch (interfaceID) 
	{
		case 1:
			break;
		default:
			break;
	}
}
// Private methods
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
		mapLanguage.emplace(key, value);
	}
	return true;
}
