#include "Log.h"
#include <fstream>
#include <ctime>

Log::Log(string path)
{
    this->path = path;
}

bool Log::info(string text)
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

void Log::setPath ( string path)
{
    this->path = path;
}

string Log::getPath()
{
    return this->path;
}

Log::~Log()
{

}