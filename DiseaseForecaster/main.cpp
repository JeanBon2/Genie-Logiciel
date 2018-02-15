#include <QtCore/QCoreApplication>
#include <string>
#define DEBUG
#include "Interface.h"
using namespace std;

int main(int argc, char *argv[])
{

	Interface test = Interface();
	string languageFilePath(R"(.\Language\FR_fr.lng)");
	test.loadMap(languageFilePath);
	QCoreApplication a(argc, argv);
	return a.exec();
}
