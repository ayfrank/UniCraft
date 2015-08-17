#pragma once

#include <BWAPI.h>
#include <BWTA.h>
#include "KnowledgeBase.h"
#include "Utility.h"

using namespace std;
using namespace BWAPI;
using namespace BWTA;

class Tactic
{
	public:
		Tactic(KnowledgeBase*, Utility*);
		~Tactic();
		virtual void execute() = 0;

	protected:
		KnowledgeBase* knowledgeBase;
		Utility* utility;
};

