#ifndef CSVPARSER_H
#define CSVPARSER_H

// System include
#include <QFile>
#include <vector>
#include <string>
using namespace std;

// Personnal include

// Constants

// Types

// Class
class CsvParser
{
	// Attributes
private:
	string content;

	// Methods
public:
	// Constructors
	CsvParser(QFile &file);
	CsvParser(string &);

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