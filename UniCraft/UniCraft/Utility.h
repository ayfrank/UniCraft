#pragma once

#include "BuildingOrdersManager.h"
#include "KnowledgeBase.h"
//#include <mutex>

DWORD WINAPI AnalyzeThread();

class Utility
{
	public:
		Utility(KnowledgeBase*);
		~Utility();

		BuildingOrdersManager* getBuildingOrdersManager();

		void analyze();

		/*bool isAnalyzed();
		void setAnalyzed(bool);*/

	private:
		BuildingOrdersManager* buildingOrdersManager;

		//mutex analyzedLock;
};

