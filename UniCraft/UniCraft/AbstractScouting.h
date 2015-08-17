#pragma once

#include "Tactic.h"

class AbstractScouting : public Tactic
{
	public:
		AbstractScouting(KnowledgeBase*, Utility*);
		~AbstractScouting();
};

