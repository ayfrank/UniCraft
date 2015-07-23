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

	if (!enemyBasesPositions.empty() && marines.size() >= 10)
	{
		auto it = enemyBasesPositions.begin();
		Position enemyBase = (*it);

		for each (auto marine in marines)
			marine->attack(enemyBase);
	}
}
