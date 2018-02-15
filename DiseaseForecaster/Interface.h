#ifndef INTERFACE_H
#define INTERFACE_H

// System include
using namespace std;
#include <iostream>
#include <stack>
#include <unordered_map>
#include <string>
// Personnal include

// Constants


// Types

// Class
class Interface
{
	// Attributes
public:
	
	
protected:
	const enum interfaceList
	{
		MENU_INTERFACE,
		ANALYSE_INTERFACE,
		UPDATE_INTERFACE,
		SEARCH_INTERFACE
	};
	static unordered_map< string,  string> texts;
	static stack<interfaceList> stackInterface;

	
private:
	


	// Methods
public:
	// Constructors
	Interface();
	// Destructors
	~Interface();

	// Others
	static bool loadMap(const string path);
	
protected:
	void previous();

	string getText(string keyMessage);
	
	virtual void getInterfaceText()=0;

	virtual string getAction()=0;

	void createInterface(const interfaceList interfaceID);

private:
};

#endif 