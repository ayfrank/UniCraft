#include "UnderAttack.h"


UnderAttack::UnderAttack(KnowledgeBase* knowledgeBase)
{
	this->knowledgeBase = knowledgeBase;
}


UnderAttack::~UnderAttack()
{
}

bool UnderAttack::operation()
{
	auto units = Broodwar->self()->getUnits();

	for (auto it = units.begin(); it != units.end(); it++)
	{
		Unit unit = (*it);

		if (unit && unit->isUnderAttack() && knowledgeBase->isNotAttacking(unit->getID()) && knowledgeBase->getScout() != unit->getID())
			return true;
	}
	return false;
}
