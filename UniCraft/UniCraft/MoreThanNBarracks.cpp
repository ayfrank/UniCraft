#include "MoreThanNBarracks.h"


MoreThanNBarracks::MoreThanNBarracks(KnowledgeBase* knowledgeBase)
{
	this->knowledgeBase = knowledgeBase;
}


MoreThanNBarracks::~MoreThanNBarracks()
{
}

bool MoreThanNBarracks::operation()
{
	return knowledgeBase->getBarracks().size() > N;
}
