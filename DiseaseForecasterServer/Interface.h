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
		UPDATE_INTERFACE,
		EXPORT_INTERFACE,
		LEAVE_INTERFACE
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
	static void start();
	
	
protected:
	void previous();

	string getTextFromField(string keyMessage);
	static void createInterface(const interfaceList interfaceID);
	virtual void displayInterfaceText()=0;

	string getAction();
	virtual void run()=0;

	

private:
};

#endif 