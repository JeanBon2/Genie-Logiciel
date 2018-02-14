#ifndef INTERFACE_H
#define INTERFACE_H

// System include
using namespace std;
#include <iostream>
#include <stack>
#include <map>
#include <string>

// Personnal include

// Constants

// Types

// Class
class Interface
{
	// Attributes
public:
	static stack<Interface> stackInterface;
protected:
	static map<string, string> mapLanguage;
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
	
	const string getText();
	
	virtual void getInterfaceText();

	virtual string getAction();

	void createInterface(const int);

private:
	//bool LoadMap(const string path);
};

#endif 