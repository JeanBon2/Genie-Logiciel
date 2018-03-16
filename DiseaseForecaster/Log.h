#ifndef LOG_H
#define LOG_H

// System include
using namespace std;
#include <iostream>

// Class
class Log
{
	// Attributes
private:
    static const string path;

	// Methods
public:
	// Destructors
	~Log ();

	// Others
    static bool info ( const string text );
};

#endif 
