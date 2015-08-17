#pragma once

#include <BehaviorTrees.h>
#include "KnowledgeBase.h"

class IsThereAnyBarrack : public Condition
{
	public:
		IsThereAnyBarrack(KnowledgeBase*);
		~IsThereAnyBarrack();

		bool operation();

	private:
		KnowledgeBase* knowledgeBase;
};

