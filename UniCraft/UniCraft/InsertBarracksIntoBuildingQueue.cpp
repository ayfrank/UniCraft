#include "InsertBarracksIntoBuildingQueue.h"


InsertBarracksIntoBuildingQueue::InsertBarracksIntoBuildingQueue(Utility* utility, KnowledgeBase* knowledgeBase)
{
	this->utility = utility;
	this->knowledgeBase = knowledgeBase;
	barracksOrder = -1;
}


InsertBarracksIntoBuildingQueue::~InsertBarracksIntoBuildingQueue()
{
}

bool InsertBarracksIntoBuildingQueue::operation()
{
	if (!utility->getBuildingOrdersManager()->searchBuildingOrder(barracksOrder)) //If we need more barracks
	{
		vector<UnitType> buildings;

		int toBuild = BARRACKS_NUMBER - knowledgeBase->getBarracks().size();

		for (int i = 0; i < toBuild; i++)
			buildings.push_back(UnitTypes::Terran_Barracks);

		barracksOrder = utility->getBuildingOrdersManager()->insertBuildingOrder(buildings, Priority::MID);
	}

	return true;
}
