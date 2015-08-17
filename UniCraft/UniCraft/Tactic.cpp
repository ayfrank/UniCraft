#include "Tactic.h"


Tactic::Tactic(KnowledgeBase* knowledgeBase, Utility* utility)
{
	this->knowledgeBase = knowledgeBase;
	this->utility = utility;
}


Tactic::~Tactic()
{
}