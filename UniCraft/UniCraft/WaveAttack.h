#pragma once

#include "AbstractAttack.h"

class WaveAttack : public AbstractAttack
{
	public:
		WaveAttack(KnowledgeBase*, Utility*);
		~WaveAttack();

		void execute();

		bool isFirstAttack();

	private:
		set<int> marines;
		set<int> attackingMarines;
		set<Position, enemyBasesComparator> enemyBasePositions;

		bool firstAttack;

		void moveToAttack();
};

