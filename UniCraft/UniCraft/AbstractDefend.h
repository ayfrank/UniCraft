#pragma once

#include "Tactic.h"

class AbstractDefend : public Tactic
{
	public:
		AbstractDefend(KnowledgeBase*, Utility*);
		~AbstractDefend();
};

