#include <QtCore/QCoreApplication>
#define DEBUG 1

#include "Log.h"
#include "Interface.h"
#include "SearchInterface.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	Interface::loadMap(R"(.\Language\Fr_fr.lng)");
	SearchInterface test = SearchInterface();
	QCoreApplication a(argc, argv);

	return a.exec();
}
