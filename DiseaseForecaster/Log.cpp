#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <iomanip> 

#include "Log.h"

const string Log::path = ".\\Ressources\\forecaster.log";

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
			setfill('0') << setw(2) << currentTimeUTC->tm_mon << "-" <<// A rendre plus propre
			setfill('0') << setw(2) << currentTimeUTC->tm_mday << " " <<
			setfill('0') << setw(2) << currentTimeUTC->tm_hour << ":" <<
			setfill('0') << setw(2) << currentTimeUTC->tm_min << ":" <<
			setfill('0') << setw(2) << currentTimeUTC->tm_sec	<< "] : " << text << endl;


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
