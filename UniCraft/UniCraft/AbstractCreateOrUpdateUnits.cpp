#include "AbstractCreateOrUpdateUnits.h"


AbstractCreateOrUpdateUnits::AbstractCreateOrUpdateUnits(KnowledgeBase* knowledgeBase, Utility* utility) : Tactic(knowledgeBase, utility)
{
}


AbstractCreateOrUpdateUnits::~AbstractCreateOrUpdateUnits()
{
}

void AbstractCreateOrUpdateUnits::execute()
{
	auto units = Broodwar->self()->getUnits();

	for (auto it = units.begin(); it != units.end(); it++)
	{
		int ID = (*it)->getID();

		if ((*it)->getHitPoints() > 0 && knowledgeBase->getScout() != ID && (*it)->isCompleted() && !(*it)->getType().isBuilding())// (knowledgeBase->getScoutID() != ID &&  --- && (*it)->isIdle())
		{
			if ((*it)->getType() == UnitTypes::Terran_SCV)
				knowledgeBase->addWorker(ID);
			else
				if ((*it)->getType() == UnitTypes::Terran_Marine && knowledgeBase->isNotAttacking(ID))
					knowledgeBase->addMarine(ID);
		}
	}
}
