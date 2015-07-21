#pragma once

#include "KnowledgeBase.h"

class Tactic
{
	public:
		Tactic();
		~Tactic();
		virtual void execute() = 0;

	private:
		KnowledgeBase* knowledgeBase;
};

