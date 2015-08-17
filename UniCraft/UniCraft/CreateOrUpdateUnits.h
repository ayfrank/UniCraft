#pragma once

#include "AbstractCreateOrUpdateUnits.h"

class CreateOrUpdateUnits : public AbstractCreateOrUpdateUnits
{
	public:
		CreateOrUpdateUnits(KnowledgeBase*, Utility*);
		~CreateOrUpdateUnits();

		void execute();
		
	private:
		const int SUPPLY_THRESHOLD = 5; //Since zerglings take 0.5 supply, the supply values in the API are doubled compared to what you would expect. Thus if self.supplyTotal() - self.supplyUsed() == 2, we can only build one Marine.
		
		int supplyDepotsOrder;
		int barracksOrder;
};

