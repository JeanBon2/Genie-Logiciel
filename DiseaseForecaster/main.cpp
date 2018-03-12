#include "Log.h"
#include "Interface.h"
#include "DbManager.h"


int main()
{
	DbManager db("DiseaseForecaster.db");
	db.getAnalyseResults("");

	if (Interface::loadMap(R"(.\Ressources\Fr_rr.lng)"))
	{
		Log::info("ça démarre");
		Interface::start();
		Log::info("ça termine");
	}

	return 0;
}
