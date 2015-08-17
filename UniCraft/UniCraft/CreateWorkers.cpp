#include "CreateWorkers.h"


CreateWorkers::CreateWorkers(KnowledgeBase* knowledgeBase, Utility* utility) : AbstractCreateOrUpdateUnits(knowledgeBase, utility)
{
}


CreateWorkers::~CreateWorkers()
{
}

void CreateWorkers::execute()
{
	AbstractCreateOrUpdateUnits::execute();

	Unit commandCenter = Broodwar->getUnit(knowledgeBase->getCommandCenter());

	if (knowledgeBase->getWorkers().size() < 20) //Train workers
	{
		if (commandCenter && commandCenter->exists() && commandCenter->getHitPoints() > 0 && commandCenter->isIdle())
		{
			Unit commandCenter = Broodwar->getUnit(knowledgeBase->getCommandCenter());
			commandCenter->train(commandCenter->getType().getRace().getWorker());
		}
	}
}
