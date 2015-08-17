#pragma once

#include <BehaviorTrees.h>
#include "Tactic.h"
#include "Strategy.h"

class TacticAction : public Action
{
public:
		TacticAction(Tactic*, Strategy*);
		~TacticAction();
		
		bool operation();

	private:
		Tactic* tactic;
		Strategy* behaviorTrees;
};

