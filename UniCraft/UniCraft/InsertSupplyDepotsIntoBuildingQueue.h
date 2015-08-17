#pragma once

#include <BehaviorTrees.h>
#include "Utility.h"

class InsertSupplyDepotsIntoBuildingQueue :	public Action
{
	public:
		InsertSupplyDepotsIntoBuildingQueue(Utility*);
		~InsertSupplyDepotsIntoBuildingQueue();

		bool operation();

	private:
		Utility* utility;

		int supplyDepotsOrder;
};

