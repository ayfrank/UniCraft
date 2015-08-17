#pragma once

#include <BWAPI.h>
#include "BuildingOrder.h"
#include "KnowledgeBase.h"

using namespace std;
using namespace BWAPI;

class BuildingOrdersManager
{
	public:
		BuildingOrdersManager(KnowledgeBase*);
		~BuildingOrdersManager();

		int insertBuildingOrder(UnitType, Priority);
		int insertBuildingOrder(vector<UnitType>, Priority);

		bool searchBuildingOrder(int);

		BuildingOrder* getBuildingOrder();

		bool removeBuildingOrder(int);
		bool deleteBuildingOrder(int);

		unordered_map<int, BuildingOrder*> getBuildingOrders();

	private:
		KnowledgeBase* knowledgeBase;
		
		int orderNumber;

		unordered_map<int, BuildingOrder*> buildingOrders;
		
		void insertIntoPriorityQueue(BuildingOrder*, Priority);

		list<BuildingOrder*> priorityQueue;

};

