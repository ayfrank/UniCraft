#pragma once

#include "AbstractDefend.h"

class Defend : public AbstractDefend
{
	public:
		Defend(KnowledgeBase*, Utility*);
		~Defend();
		void execute();
};

