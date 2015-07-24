#pragma once

#include "AbstractCreateOrUpdateUnits.h"

class CreateOrUpdateUnits :	public AbstractCreateOrUpdateUnits
{
	public:
		CreateOrUpdateUnits();
		~CreateOrUpdateUnits();

		void execute();

	private:
		const int SUPPLY_THRESHOLD = 2;
};

