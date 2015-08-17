#pragma once

#include "Tactic.h"

class AbstractCollectResources : public Tactic
{
	public:
		AbstractCollectResources(KnowledgeBase*, Utility*);
		~AbstractCollectResources();
};

