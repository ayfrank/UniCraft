#include "BuildBuildings.h"
#include "BuildBuildings.h"


BuildBuildings::BuildBuildings()
{
}


BuildBuildings::~BuildBuildings()
{
}

void BuildBuildings::execute()
{
	if(knowledgeBase->getBarracks().size() == 0 && Broodwar->self()->minerals() >= 400)
	{
		UnitInterface* commandCenter = knowledgeBase->getCommandCenter();

		if(commandCenter != NULL && commandCenter->exists())
		{
			Unit barrackBuilder = commandCenter->getClosestUnit(Filter::GetType == UnitTypes::Terran_Barracks.whatBuilds().first &&
				(Filter::IsIdle || Filter::IsGatheringMinerals) &&
				Filter::IsOwned); //Search a worker to build barrack, the closest to the command center

			if(barrackBuilder)
			{
				TilePosition targetBuildLocation = Broodwar->getBuildLocation(UnitTypes::Terran_Barracks, barrackBuilder->getTilePosition());
				if (targetBuildLocation)
					barrackBuilder->build(UnitTypes::Terran_Barracks, targetBuildLocation);
			}
		}
	}
}
