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

	for each (auto worker in workers)
	{
		if(worker->isCarryingGas() || worker->isCarryingMinerals())
			worker->returnCargo();
		else
			if(!worker->getPowerUp())
				if (!worker->gather(worker->getClosestUnit(Filter::IsMineralField || Filter::IsRefinery)))
					Broodwar << Broodwar->getLastError() << endl;
	}
}
