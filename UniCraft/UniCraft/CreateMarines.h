#pragma once

#include "AbstractCreateOrUpdateUnits.h"

class CreateMarines : public AbstractCreateOrUpdateUnits
{
	public:
		CreateMarines(KnowledgeBase*, Utility*);
		~CreateMarines();

		void execute();
};

