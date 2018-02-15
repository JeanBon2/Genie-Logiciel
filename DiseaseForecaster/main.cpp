#include <QtCore/QCoreApplication>
#include "Log.h"
#include "Interface.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{

	Log::Info("Test");
	QCoreApplication a(argc, argv);

	return a.exec();
}
