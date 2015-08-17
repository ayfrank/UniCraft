#include "IsBuildingQueueEmpty.h"


IsBuildingQueueEmpty::IsBuildingQueueEmpty(Utility* utility)
{
	this->utility = utility;
}


IsBuildingQueueEmpty::~IsBuildingQueueEmpty()
{
}

bool IsBuildingQueueEmpty::operation()
{
	return utility->getBuildingOrdersManager()->getBuildingOrders().size() == 0;
}