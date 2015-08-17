#include "Utility.h"


Utility::Utility(KnowledgeBase* knowledgeBase)
{
	buildingOrdersManager = new BuildingOrdersManager(knowledgeBase);
}


Utility::~Utility()
{
	delete buildingOrdersManager;
}

BuildingOrdersManager* Utility::getBuildingOrdersManager()
{
	return buildingOrdersManager;
}

/*bool Utility::isAnalyzed()
{
	//analyzedLock.lock();
	return analyzed;
	//analyzedLock.unlock();
}

void Utility::setAnalyzed(bool analyzed)
{
	//analyzedLock.lock();
	this->analyzed = analyzed;
	//analyzedLock.unlock();
}*/

DWORD WINAPI AnalyzeThread()
{
	Broodwar << "START ANALYZING" << endl;
	readMap();
	analyze();
	//knowledgeBase->setAnalyzed(true);
	Broodwar << "END ANALYZING" << endl;
	return 0;
}

void Utility::analyze()
{
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AnalyzeThread, NULL, 0, NULL);
}