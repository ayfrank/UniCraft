#include "InsertSupplyDepotsIntoBuildingQueue.h"


InsertSupplyDepotsIntoBuildingQueue::InsertSupplyDepotsIntoBuildingQueue(Utility* utility)
{
	this->utility = utility;
}


InsertSupplyDepotsIntoBuildingQueue::~InsertSupplyDepotsIntoBuildingQueue()
{
}

bool InsertSupplyDepotsIntoBuildingQueue::operation()
{
	if (!utility->getBuildingOrdersManager()->searchBuildingOrder(supplyDepotsOrder)) //If we need more supply depot
		supplyDepotsOrder = utility->getBuildingOrdersManager()->insertBuildingOrder(UnitTypes::Terran_Supply_Depot, Priority::HIGH);

	return true;
}
