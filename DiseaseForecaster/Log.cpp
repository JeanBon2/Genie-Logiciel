#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

#include "Log.h"

const string Log::path = "forecaster.log";

Log::Log()
{}

bool Log::Info(const string text)
{
    ofstream file(path);
    
    if ( file )
    {
		streambuf *oldCoutBuffer = cout.rdbuf(file.rdbuf());

        time_t result = time(nullptr);
        cout << "[ " << asctime(localtime(&result)) << " ] : " << text << endl;


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