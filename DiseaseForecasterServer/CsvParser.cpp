// System include
#include <iostream>
#include<sstream>
using namespace std;

// Personnal include
#include "CsvParser.h"

// Constants

// Constructors
CsvParser::CsvParser(QFile& fileToParse) : content("")
{
#ifdef DEBUG
	cout << "CsvParser constructor call" << endl;
#endif // DEBUG
	if (!fileToParse.open(QIODevice::ReadOnly))
	{
		// Call log
		return;
	}
	content = fileToParse.readAll().toStdString();
	fileToParse.close();
}
CsvParser::CsvParser(string content) : content(content)
{
#ifdef DEBUG
	cout << "CsvParser constructor call" << endl;
#endif // DEBUG
}


// Destructor
CsvParser::~CsvParser()
{
#ifdef DEBUG
	cout << "Xxx destructor call" << endl;
#endif // DEBUG
}

// Public methods
vector<vector<string>> CsvParser::parse()
{
	if (!parsedContent.empty())
	{
		// If the content has already been parsed, it is immediatly returned
		return parsedContent;
	}

	istringstream lineIss(content);
	string line;
	while(getline(lineIss, line))
	{
		vector<string> parsedLine;
		istringstream wordIss(line);
		string word;
		while(getline(wordIss, word, ';'))
		{
			parsedLine.push_back(word);
		}
		parsedContent.push_back(parsedLine);
	}

	return parsedContent;
}

vector<vector<string>> CsvParser::staticParse(QFile& file)
{
	CsvParser csvParser(file);
	return csvParser.parse();
}

vector<vector<string>> CsvParser::staticParse(string content)
{
	CsvParser csvParser(content);
	return csvParser.parse();
}
