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
	vector<vector<string> > parsedContent;

	// Methods
public:
	// Constructors
	CsvParser(QFile &file);
	CsvParser(string content);

	// Destructors
	~CsvParser();

	// Others
	const vector<vector<string> > parse();
	static const vector<vector<string> > staticParse(QFile &file);
	static const vector<vector<string> > staticParse(string content);
};

#endif // CSVPARSER_H