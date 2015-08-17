#include "CollectResources.h"


CollectResources::CollectResources(KnowledgeBase* knowledgeBase, Utility* utility) : AbstractCollectResources(knowledgeBase, utility)
{
}


CollectResources::~CollectResources()
{
}

void CollectResources::execute()
{
	workers = knowledgeBase->getWorkers();

	for (auto it = workers.begin(); it != workers.end(); it++)
	{
		Unit currentWorker = Broodwar->getUnit((*it));

		if (!currentWorker->exists() || currentWorker->getHitPoints() <= 0)
			knowledgeBase->removeWorker((*it));
		else
		{
			if (currentWorker->isIdle())
			{
				Unit commandCenter = Broodwar->getUnit(knowledgeBase->getCommandCenter());
				if (commandCenter && commandCenter->exists() && commandCenter->getHitPoints() > 0)
				{
					if (currentWorker->isCarryingGas() || currentWorker->isCarryingMinerals())
						currentWorker->returnCargo();
					else
						if (!currentWorker->getPowerUp())
							if (!currentWorker->gather(currentWorker->getClosestUnit(Filter::IsMineralField))) // || Filter::IsRefinery - radius 500
								Broodwar << Broodwar->getLastError() << endl;
				}
			}
		}
	}
}
