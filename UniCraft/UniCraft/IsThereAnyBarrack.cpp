#include "IsThereAnyBarrack.h"


IsThereAnyBarrack::IsThereAnyBarrack(KnowledgeBase* knowledgeBase)
{
	this->knowledgeBase = knowledgeBase;
}


IsThereAnyBarrack::~IsThereAnyBarrack()
{
}

bool IsThereAnyBarrack::operation()
{
	return knowledgeBase->getBarracks().size() > 0;
}
