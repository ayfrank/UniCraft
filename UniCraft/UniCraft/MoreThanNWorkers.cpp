#include "MoreThanNWorkers.h"


MoreThanNWorkers::MoreThanNWorkers(KnowledgeBase* knowledgeBase)
{
	this->knowledgeBase = knowledgeBase;
}


MoreThanNWorkers::~MoreThanNWorkers()
{
}

bool MoreThanNWorkers::operation()
{
	return knowledgeBase->getWorkers().size() >= N;
}
