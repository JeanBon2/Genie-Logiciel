#ifndef INTERFACE_H
#define INTERFACE_H

// System include
using namespace std;
#include <iostream>
#include <stack>
#include <map>
// Personnal include

// Constants
const enum interfaceEnum {
	MENU_INTERFACE,
	SEARCH_INTERFACE,
	UPDATE_INTERFACE,
	ANALYSE_INTERFACE
};

// Types

// Class
class Interface
{
	// Attributes
public:
	static stack<Interface> stackInterface;

protected:

private:
	static map<string, string> mapLanguage;

	// Methods
public:
	// Constructors
	Interface();
	Interface(const Interface* x);

	// Destructors
	~Interface();

	// Others
	
protected:
	void previous();
	
	string getText(string keyMessage);
	
	virtual string getInterfaceText();

	virtual string getAction();

	void createInterface(int);

private:
};

#endif 