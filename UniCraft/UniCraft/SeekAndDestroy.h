#pragma once

#include "AbstractAttack.h"

class SeekAndDestroy :	public AbstractAttack
{
	public:
		SeekAndDestroy(KnowledgeBase*, Utility*);
		~SeekAndDestroy();

		void execute();

	private:
		set<int> attackingMarines;
};

