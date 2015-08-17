#pragma once

#include <BehaviorTrees.h>
#include <BWAPI.h>
#include "Utility.h"

using namespace BWAPI;

class InsertCommandCenterIntoBuildingQueue : public Action
{
	public:
		InsertCommandCenterIntoBuildingQueue(Utility*);
		~InsertCommandCenterIntoBuildingQueue();

		bool operation();

	private:
		Utility* utility;
		int commandCenterOrder;
};

