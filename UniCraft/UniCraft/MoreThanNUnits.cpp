#include "MoreThanNUnits.h"


MoreThanNUnits::MoreThanNUnits()
{
}


MoreThanNUnits::~MoreThanNUnits()
{
}

bool MoreThanNUnits::operation()
{
	return Broodwar->self()->completedUnitCount(UnitTypes::Terran_SCV) >= N;
}
