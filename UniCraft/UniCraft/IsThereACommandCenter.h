#pragma once

#include <BehaviorTrees.h>
#include "KnowledgeBase.h"

class IsThereACommandCenter : public Leaf
{
	public:
		IsThereACommandCenter(KnowledgeBase*);
		~IsThereACommandCenter();

		bool operation();

	private:
		KnowledgeBase* knowledgeBase;
};

