#include "LessThanNMarines.h"


LessThanNMarines::LessThanNMarines(KnowledgeBase* knowledgeBase, int marinesNumber)
{
	this->knowledgeBase = knowledgeBase;
	this->marinesNumber = marinesNumber;
}


LessThanNMarines::~LessThanNMarines()
{
}

bool LessThanNMarines::operation()
{
	return knowledgeBase->getMarines().size() < marinesNumber;
}
