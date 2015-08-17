#include "CreateMarines.h"


CreateMarines::CreateMarines(KnowledgeBase* knowledgeBase, Utility* utility) : AbstractCreateOrUpdateUnits(knowledgeBase, utility)
{
}


CreateMarines::~CreateMarines()
{
}

void CreateMarines::execute()
{
	AbstractCreateOrUpdateUnits::execute();

	set< int > barracks = knowledgeBase->getBarracks();

	for (auto it = barracks.begin(); it != barracks.end(); it++) //Train marines
	{
		Unit barrack = Broodwar->getUnit((*it));
		if (barrack && barrack->exists() && barrack->getHitPoints() > 0 && barrack->isIdle())
			barrack->train(UnitTypes::Terran_Marine);
	}
}