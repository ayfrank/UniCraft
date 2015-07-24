#pragma once

#include "AbstractBuildBuildings.h"

class BuildBuildings : public AbstractBuildBuildings
{
	public:
		BuildBuildings();
		~BuildBuildings();

		void execute();
};

