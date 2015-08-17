#pragma once

#include <BehaviorTrees.h>
#include "Utility.h"

class InsertBarracksIntoBuildingQueue : public Action
{
	public:
		InsertBarracksIntoBuildingQueue(Utility*, KnowledgeBase*);
		~InsertBarracksIntoBuildingQueue();

		bool operation();

	private:
		Utility* utility;
		KnowledgeBase* knowledgeBase;
		int barracksOrder;
		const int BARRACKS_NUMBER = 4;
};

