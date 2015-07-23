#pragma once

#include <BWAPI.h>
#include <BWTA.h>
#include "KnowledgeBase.h"

using namespace std;
using namespace BWAPI;
using namespace BWTA;

class Tactic
{
	public:
		Tactic();
		~Tactic();
		virtual void execute() = 0;

	protected:
		KnowledgeBase* knowledgeBase;
};

