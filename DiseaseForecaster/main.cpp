#include <QtCore/QCoreApplication>
#include <windows.h>

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	char* buffer = new char[500];
	GetModuleFileNameA(nullptr, buffer, 500);
	cout << buffer << endl;
	delete[]buffer;
	 
	QCoreApplication a(argc, argv);

	return a.exec();
}
