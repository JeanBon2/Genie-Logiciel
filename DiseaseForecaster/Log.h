#ifndef LOG_H
#define LOG_H

// System include
using namespace std;
#include <iostream>
// Personnal include

// Constants

// Types

// Class
class Log
{
	// Attributes
public:

protected:

private:
		static string path; 

	// Methods
public:
	// Constructors
	Log ( string path );

    static bool info ( string text );

    void setPath ( string path);

    string getPath ();

	// Destructors
	~Log ();

	// Others
	
protected:

private:
};

#endif 