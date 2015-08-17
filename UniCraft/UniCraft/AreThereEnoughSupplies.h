#pragma once

#include <BehaviorTrees.h>
#include <BWAPI.h>

using namespace BWAPI;

class AreThereEnoughSupplies :	public Condition
{
	public:
		AreThereEnoughSupplies();
		~AreThereEnoughSupplies();

		bool operation();

	private:
		const int SUPPLY_THRESHOLD = 5; //Since zerglings take 0.5 supply, the supply values in the API are doubled compared to what you would expect. Thus if self.supplyTotal() - self.supplyUsed() == 2, we can only build one Marine.

};

