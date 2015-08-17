#include "InsertCommandCenterIntoBuildingQueue.h"


InsertCommandCenterIntoBuildingQueue::InsertCommandCenterIntoBuildingQueue(Utility* utility)
{
	this->utility = utility;
	commandCenterOrder = -1;
}


InsertCommandCenterIntoBuildingQueue::~InsertCommandCenterIntoBuildingQueue()
{
}

bool InsertCommandCenterIntoBuildingQueue::operation()
{
	if (!utility->getBuildingOrdersManager()->searchBuildingOrder(commandCenterOrder))
		commandCenterOrder = utility->getBuildingOrdersManager()->insertBuildingOrder(UnitTypes::Terran_Command_Center, Priority::HIGH);
	
	return true;
}
