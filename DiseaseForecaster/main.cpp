#include "Log.h"
#include "Interface.h"
#include "DbManager.h"


int main()
{
	if (Interface::loadMap(R"(.\Ressources\Fr_rr.lng)"))
	{
		Interface::start();
	}

	return 0;
}
