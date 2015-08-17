#include "SeekAndDestroy.h"


SeekAndDestroy::SeekAndDestroy(KnowledgeBase* knowledgeBase, Utility* utility) : AbstractAttack(knowledgeBase, utility)
{
}


SeekAndDestroy::~SeekAndDestroy()
{
}

void SeekAndDestroy::execute()
{
	attackingMarines = knowledgeBase->getAttackingMarines();

	for (auto it = attackingMarines.begin(); it != attackingMarines.end(); it++)
	{
		int marineID = (*it);
		Unit u = Broodwar->getUnit(marineID);

		if (!u->exists() || u->getHitPoints() <= 0)
			knowledgeBase->removeMarine(marineID);
		else
			if (u->exists() && u->getHitPoints() > 0 && !(u->isUnderAttack() || u->getOrder() == Orders::AttackMove || u->getOrder() == Orders::AttackUnit || u->getOrder() == Orders::AttackTile)) //Prendi unità nemica più vicina e attaccala  && Broodwar->enemy()->getUnits().size() > 0
				u->attack(u->getClosestUnit(Filter::IsEnemy));
	}
}
