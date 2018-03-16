#ifndef INTERFACE_H
#define INTERFACE_H

// System include
using namespace std;
#include <iostream>
#include <stack>
#include <unordered_map>
#include <string>

// Class
class Interface
{
	// Attributes
protected:
    enum interfaceList
	{
		MENU_INTERFACE,
		ANALYSE_INTERFACE,
		UPDATE_INTERFACE,
		SEARCH_INTERFACE,
		LOG_INTERFACE,
		LEAVE_INTERFACE,
		HELP_INTERFACE
	};
	static unordered_map< string,  string> texts;
	static stack<interfaceList> stackInterface;

	// Methods
public:
	// Destructors
    virtual ~Interface() = default;

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
};

#endif 
