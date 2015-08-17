#include "Defend.h"


Defend::Defend(KnowledgeBase* knowledgeBase, Utility* utility) : AbstractDefend(knowledgeBase, utility)
{
}


Defend::~Defend()
{
}

void Defend::execute()
{
	set<int> marines = knowledgeBase->getMarines();

	for (auto it = marines.begin(); it != marines.end(); it++)
	{
		Unit marine = Broodwar->getUnit((*it));

		if (!marine->exists() || marine->getHitPoints() <= 0)
			knowledgeBase->removeMarine((*it));
		else
			if (!(!marine->isCompleted() || marine->isConstructing()) && marine->isIdle())
				marine->attack(marine->getClosestUnit(Filter::IsEnemy));
	}
}