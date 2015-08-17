#include "Manager.h"

Manager::Manager(Strategy* strategy)
{
	this->strategy = strategy;
}

Manager::~Manager()
{
}

void Manager::performActionsOfThisStep()
{
	if (BroodwarPtr != NULL)
	{
		strategy->compute();
		strategy->executeActionOfThisStep();
		/*t4->execute();
		t3->execute();
		t->execute();		
		//Broodwar->drawTextScreen(200, 100, "Scout ID: %i", knowledgeBase->getScoutID());

		//if (Broodwar->self()->supplyUsed()/2 >= 10)
		if (Broodwar->getFrameCount() >= 60*2*20)
			t2->execute();

		t5->execute();
		t6->execute();*/
	}
}
