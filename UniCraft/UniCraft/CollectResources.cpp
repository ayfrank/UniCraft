#include "CollectResources.h"


CollectResources::CollectResources()
{
}


CollectResources::~CollectResources()
{
}

void CollectResources::execute()
{
	workers = knowledgeBase->getWorkers();

	for(auto it = workers.begin(); it != workers.end(); it++)
	{
		if(!(*it)->exists())
			workers.erase(it);
		else
		{
			if((*it)->isIdle())
			{
				if ((*it)->isCarryingGas() || (*it)->isCarryingMinerals())
					(*it)->returnCargo();
				else
					if (!(*it)->getPowerUp())
						if (!(*it)->gather((*it)->getClosestUnit(Filter::IsMineralField || Filter::IsRefinery)))
							Broodwar << Broodwar->getLastError() << endl;
			}
		}
	}
}
