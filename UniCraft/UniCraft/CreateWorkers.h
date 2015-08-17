#pragma once

#include "AbstractCreateOrUpdateUnits.h"

class CreateWorkers : public AbstractCreateOrUpdateUnits
{
	public:
		CreateWorkers(KnowledgeBase*, Utility*);
		~CreateWorkers();

		void execute();
};

