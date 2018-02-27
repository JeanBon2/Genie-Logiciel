#include "Log.h"
#include "Interface.h"

int main(int argc, char *argv[])
{
	if (Interface::loadMap(R"(.\Ressources\Fr_fr.lng)"))
	{
		Log::info("ça démarre");
		Interface::start();
		Log::info("ça termine");
	}

	return 0;
}
