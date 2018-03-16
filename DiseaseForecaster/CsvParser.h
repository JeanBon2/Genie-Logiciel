#ifndef CSVPARSER_H
#define CSVPARSER_H

// System include
#include <QFile>
#include <vector>
#include <string>
using namespace std;

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
	vector<vector<string> > parse();
	static vector<vector<string> > staticParse(QFile &file);
	static vector<vector<string> > staticParse(string content);
};

#endif // CSVPARSER_H
