#pragma once

#include <BehaviorTrees.h>
#include "WaveAttack.h"

class IsNotFirstAttack : public Condition
{
	public:
		IsNotFirstAttack(Tactic*);
		~IsNotFirstAttack();

		bool operation();

	private:
		Tactic* waveAttack;
};

