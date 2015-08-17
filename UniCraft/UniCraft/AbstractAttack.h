#pragma once

#include "Tactic.h"

class AbstractAttack : public Tactic
{
	public:
		AbstractAttack(KnowledgeBase*, Utility*);
		~AbstractAttack();
};

