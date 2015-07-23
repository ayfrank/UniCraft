#pragma once

#include "AbstractCollectResources.h"

class CollectResources : public AbstractCollectResources
{
	public:
		CollectResources();
		~CollectResources();

		void execute();

	private:
		vector< UnitInterface* > workers;
};

