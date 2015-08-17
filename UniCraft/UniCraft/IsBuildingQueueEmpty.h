#pragma once

#include <BehaviorTrees.h>
#include "Utility.h"

class IsBuildingQueueEmpty : public Condition
{
	public:
		IsBuildingQueueEmpty(Utility*);
		~IsBuildingQueueEmpty();

		bool operation();

	private:
		Utility* utility;
};

