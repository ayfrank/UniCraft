#pragma once

#include "KnowledgeBase.h"

class Strategy
{
	public:
		Strategy();
		~Strategy();
		virtual void getActionsToExecuteInThisStep() = 0; //Return collection of Tactics

	private:
		//Collection of Tactics
		KnowledgeBase* knowledgeBase;
};