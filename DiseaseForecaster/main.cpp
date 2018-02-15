#include <QtCore/QCoreApplication>
#define DEBUG 1

#include "Log.h"
#include "Interface.h"
#include "SearchInterface.h"
#include "MenuInterface.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	Interface::loadMap(R"(.\Language\Fr_fr.lng)");

	MenuInterface menu = MenuInterface();

	QCoreApplication a(argc, argv);

	return a.exec();
}
