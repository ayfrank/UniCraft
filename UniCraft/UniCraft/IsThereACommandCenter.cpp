#include "IsThereACommandCenter.h"


IsThereACommandCenter::IsThereACommandCenter(KnowledgeBase* knowledgeBase)
{
	this->knowledgeBase = knowledgeBase;
}


IsThereACommandCenter::~IsThereACommandCenter()
{
}

bool IsThereACommandCenter::operation()
{
	int commandCenterID = knowledgeBase->getCommandCenter();
	Unit commandCenter = Broodwar->getUnit(commandCenterID);

	return commandCenterID != -1 && commandCenter && commandCenter->exists() && commandCenter->getHitPoints() > 0;
}