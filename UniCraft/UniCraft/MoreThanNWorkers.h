#pragma once

#include <BehaviorTrees.h>
#include "KnowledgeBase.h"

class MoreThanNWorkers : public Condition
{
	public:
		MoreThanNWorkers(KnowledgeBase*);
		~MoreThanNWorkers();

		bool operation();

	private:
		KnowledgeBase* knowledgeBase;
		const unsigned int N = 20;
};

