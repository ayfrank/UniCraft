#include "WaveAttack.h"


WaveAttack::WaveAttack(KnowledgeBase* knowledgeBase, Utility* utility) : AbstractAttack(knowledgeBase, utility)
{
	firstAttack = false;
}


WaveAttack::~WaveAttack()
{
}

void WaveAttack::execute()
{
	marines = knowledgeBase->getMarines();
	attackingMarines = knowledgeBase->getAttackingMarines();
	enemyBasePositions = knowledgeBase->getEnemyBasePositions();

	if (!enemyBasePositions.empty())
	{
		moveToAttack();
		firstAttack = true;
	}
}

void WaveAttack::moveToAttack()
{
	auto it = enemyBasePositions.begin();
	Position enemyBase = (*it);

	for (auto it = marines.begin(); it != marines.end(); it++)
	{
		Unit marine = Broodwar->getUnit((*it));

		if (!marine->exists() || marine->getHitPoints() <= 0)
			knowledgeBase->removeMarine((*it));
		else
			if (!(!marine->isCompleted() || marine->isConstructing()) && marine->isIdle())
			{
				marine->attack(enemyBase);
				knowledgeBase->addAttackingMarine((*it));
				knowledgeBase->removeMarine((*it));
			}
	}
}

bool WaveAttack::isFirstAttack()
{
	return firstAttack;
}
