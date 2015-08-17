#pragma once

#include <BehaviorTrees.h>
#include <BWAPI.h>
#include "KnowledgeBase.h"

using namespace BWAPI;

class UnderAttack : public Condition
{
	public:
		UnderAttack(KnowledgeBase*);
		~UnderAttack();

		bool operation();

	private:
		KnowledgeBase* knowledgeBase;
};

