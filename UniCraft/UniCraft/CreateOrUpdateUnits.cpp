#include "CreateOrUpdateUnits.h"
#include "CreateOrUpdateUnits.h"


CreateOrUpdateUnits::CreateOrUpdateUnits()
{
}


CreateOrUpdateUnits::~CreateOrUpdateUnits()
{
}

void CreateOrUpdateUnits::execute()
{
	int supplyTotal = Broodwar->self()->supplyTotal();
	int supplyUsed = Broodwar->self()->supplyUsed();

	if(supplyTotal - supplyUsed <= SUPPLY_THRESHOLD) //If we need more supply depot
	{
		UnitInterface* commandCenter = knowledgeBase->getCommandCenter();
		UnitType supplyProviderType = commandCenter->getType().getRace().getSupplyProvider();

		if(commandCenter != NULL && commandCenter->exists())
		{
			Unit supplyBuilder = commandCenter->getClosestUnit(Filter::GetType == supplyProviderType.whatBuilds().first &&
				(Filter::IsIdle || Filter::IsGatheringMinerals) &&
				Filter::IsOwned); //Search a worker to build supply depot, the closest to the command center

			if(supplyBuilder)
				if(supplyProviderType.isBuilding())
				{
					TilePosition targetBuildLocation = Broodwar->getBuildLocation(supplyProviderType, supplyBuilder->getTilePosition());
					if(targetBuildLocation)
						supplyBuilder->build(supplyProviderType, targetBuildLocation);
				}
		}
		else
		{
			if(knowledgeBase->getWorkers().size() <= 20) //Train workers
			{
				UnitInterface* commandCenter = knowledgeBase->getCommandCenter();
				commandCenter->train(commandCenter->getType().getRace().getWorker());
			}

			vector< UnitInterface* > barracks = knowledgeBase->getBarracks();

			if(barracks.size() > 0 && knowledgeBase->getMarines().size() < 30) //Train marines
				barracks[0]->train(UnitTypes::Terran_Marine);
		}
	}
}
