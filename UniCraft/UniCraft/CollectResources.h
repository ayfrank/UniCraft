#pragma once

#include "AbstractCollectResources.h"

class CollectResources : public AbstractCollectResources
{
	public:
		CollectResources(KnowledgeBase*, Utility*);
		~CollectResources();

		void execute();

	private:
		set<int> workers;
};

