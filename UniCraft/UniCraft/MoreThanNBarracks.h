#pragma once

#include <BehaviorTrees.h>
#include "KnowledgeBase.h"

class MoreThanNBarracks : public Condition
{
	public:
		MoreThanNBarracks(KnowledgeBase*);
		~MoreThanNBarracks();

		bool operation();

	private:
		KnowledgeBase* knowledgeBase;
		const unsigned int N = 3;
};

