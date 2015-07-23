#pragma once

#include "AbstractAttack.h"

class StupidAttack : public AbstractAttack
{
	public:
		StupidAttack();
		~StupidAttack();

		void execute();

	private:
		vector< UnitInterface* > marines;
};

