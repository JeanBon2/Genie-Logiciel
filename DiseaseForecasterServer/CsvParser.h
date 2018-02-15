#ifndef CSVPARSER_H
#define CSVPARSER_H

// System include
#include <QFile>
#include <vector>
using namespace std;

// Personnal include

// Constants

// Types

// Class
class CsvParser
{
	// Attributes
public:
	static int publicAttribute;

protected:
	char protectedAttribute;

private:
	double privateAttribute;

	// Methods
public:
	// Constructors
	CsvParser();

	// Destructors
	~CsvParser();

	// Others
	void publicMethod();

protected:
	void protectedMethod();

private:
	void privateMethod();
};

#endif // CSVPARSER_H