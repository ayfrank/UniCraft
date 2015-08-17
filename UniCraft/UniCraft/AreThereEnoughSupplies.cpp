#include "AreThereEnoughSupplies.h"


AreThereEnoughSupplies::AreThereEnoughSupplies()
{
}


AreThereEnoughSupplies::~AreThereEnoughSupplies()
{
}

bool AreThereEnoughSupplies::operation()
{
	int supplyTotal = Broodwar->self()->supplyTotal() / 2;
	int supplyUsed = Broodwar->self()->supplyUsed() / 2;

	return supplyTotal - supplyUsed > SUPPLY_THRESHOLD;
}