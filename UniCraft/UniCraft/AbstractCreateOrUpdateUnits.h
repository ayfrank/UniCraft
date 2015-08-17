#pragma once

#include "Tactic.h"

class AbstractCreateOrUpdateUnits : public Tactic
{
	public:
		AbstractCreateOrUpdateUnits(KnowledgeBase*, Utility*);
		~AbstractCreateOrUpdateUnits();

		void execute();
};

