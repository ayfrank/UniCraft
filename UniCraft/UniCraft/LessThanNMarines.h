#pragma once

#include <BehaviorTrees.h>
#include "KnowledgeBase.h"

class LessThanNMarines : public Condition
{
	public:
		LessThanNMarines(KnowledgeBase*, int);
		~LessThanNMarines();

		bool operation();

	private:
		KnowledgeBase* knowledgeBase;
		unsigned int marinesNumber;
};

