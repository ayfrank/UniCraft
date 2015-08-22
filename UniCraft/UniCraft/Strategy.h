#pragma once

#include "Tactic.h"
#include "KnowledgeBase.h"
#include "Utility.h"

class Strategy
{
	public:
		Strategy();
		~Strategy();
		virtual void performActionsOfThisStep();
		virtual void compute() = 0;

		void addTactic(Tactic*);

	protected:
		list<Tactic*> tactics;
		KnowledgeBase* knowledgeBase;
		Utility* utility;
};