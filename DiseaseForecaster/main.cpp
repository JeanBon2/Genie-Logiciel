#include "Log.h"
#include "Interface.h"
#include "DbManager.h"


int main()
{
	DbManager db("DiseaseForecaster.db");
	db.getAnalyseResults("");

	if (Interface::loadMap(R"(.\Ressources\Rr_rr.lng)"))
	{
		Log::info("�a d�marre");
		Interface::start();
		Log::info("�a termine");
	}

	return 0;
}
