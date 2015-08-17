#pragma once

#include "Tactic.h"

class AbstractBuildBuildings : public Tactic
{
	public:
		AbstractBuildBuildings(KnowledgeBase*, Utility*);
		~AbstractBuildBuildings();
};

