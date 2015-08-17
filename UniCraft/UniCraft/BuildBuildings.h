#pragma once

#include "AbstractBuildBuildings.h"

class BuildBuildings : public AbstractBuildBuildings
{
	public:
		BuildBuildings(KnowledgeBase*, Utility*);
		~BuildBuildings();

		void execute();

	private:
		BuildingOrder* processingBuildingOrder;
};

