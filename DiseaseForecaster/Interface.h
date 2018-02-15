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
	static unordered_map<string, string> mapLanguage;
private:
	


	// Methods
public:
	// Constructors
	Interface();
	Interface(const Interface* x);
	bool loadMap(const string path);
	// Destructors
	~Interface();

	// Others
	
protected:
	void previous();

	string getText(string keyMessage);
	
<<<<<<< HEAD
	string getText(string keyMessage);
=======
	const string getText();
>>>>>>> f17c52115006eb1e2633503c3375c6940e8c9946
	
	virtual void getInterfaceText();

	virtual string getAction();

	void createInterface(const int);

private:
	//bool LoadMap(const string path);
};

#endif 