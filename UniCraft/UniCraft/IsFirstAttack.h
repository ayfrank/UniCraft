#pragma once

#include <BehaviorTrees.h>
#include "WaveAttack.h"

class IsFirstAttack : public Condition
{
	public:
		IsFirstAttack(Tactic*);
		~IsFirstAttack();

		bool operation();

	private:
		Tactic* waveAttack;
};

