#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

#include "Log.h"

const string Log::path = "forecaster.log";

Log::Log()
{}

bool Log::info(const string text)
{
    ofstream file(path, ios::app);
    
    if (file)
    {
		streambuf *oldCoutBuffer = cout.rdbuf(file.rdbuf());
		time_t getTime;
		struct tm* currentTimeUTC;

		time(&getTime);
		currentTimeUTC = gmtime(&getTime);

        cout << "[" << 
			currentTimeUTC->tm_year+1900 << "-" <<
			currentTimeUTC->tm_mon << "-" <<
			currentTimeUTC->tm_mday << " " <<
			currentTimeUTC->tm_hour << ":" <<
			currentTimeUTC->tm_min << ":" <<
			currentTimeUTC->tm_sec	<< "] : " << text << endl;


        cout.rdbuf(oldCoutBuffer);
        file.close();
    }
    else
    {
        return false;
    }

    return true;
}



Log::~Log()
{

}