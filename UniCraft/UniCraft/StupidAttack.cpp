#include "StupidAttack.h"


StupidAttack::StupidAttack()
{
}


StupidAttack::~StupidAttack()
{
}

void StupidAttack::execute()
{
	marines = knowledgeBase->getMarines();
	set< Position, enemyBasesComparator > enemyBasesPositions = knowledgeBase->getEnemyBasesPositions();

	if(!enemyBasesPositions.empty() && marines.size() >= 10)
	{
		auto it = enemyBasesPositions.begin();
		Position enemyBase = (*it);

		for(auto it = marines.begin(); it != marines.end(); it++)
		{
			if(!(*it)->exists())
				marines.erase(it);
			else
				if(!(!(*it)->isCompleted() || (*it)->isConstructing()) && (*it)->isIdle())
					(*it)->attack(enemyBase);
		}
	}
}
