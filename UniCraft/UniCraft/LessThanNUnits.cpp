#include "LessThanNUnits.h"


LessThanNUnits::LessThanNUnits()
{
}


LessThanNUnits::~LessThanNUnits()
{
}

bool LessThanNUnits::operation()
{
	return Broodwar->self()->completedUnitCount(UnitTypes::Terran_SCV) < N;
}
