#include "BuildBuildings.h"
#include "BuildBuildings.h"


BuildBuildings::BuildBuildings(KnowledgeBase* knowledgeBase, Utility* utility) : AbstractBuildBuildings(knowledgeBase, utility)
{
	processingBuildingOrder = nullptr;
}


BuildBuildings::~BuildBuildings()
{
}

void BuildBuildings::execute()
{
	if (processingBuildingOrder == nullptr)
		processingBuildingOrder = utility->getBuildingOrdersManager()->getBuildingOrder();

	if (processingBuildingOrder)
	{
		Unit builder = Broodwar->getUnit(processingBuildingOrder->getBuilder());
		Unit building = Broodwar->getUnit(processingBuildingOrder->getBuilding());
		UnitType unitType = processingBuildingOrder->getUnitType();

		if (builder == nullptr || (builder != nullptr && (!builder->exists() || builder->getHitPoints() <= 0)) || (builder != nullptr && builder->getID
			() == knowledgeBase->getScout()))
		{
			Unit commandCenter = Broodwar->getUnit(knowledgeBase->getCommandCenter());

			if (commandCenter != NULL && commandCenter->exists() && commandCenter->getHitPoints() > 0 && Broodwar->self()->minerals() >= unitType.mineralPrice())
			{
				Unit builder = commandCenter->getClosestUnit(Filter::GetType == unitType.whatBuilds().first &&
					(Filter::IsIdle || Filter::IsGatheringMinerals) &&
					Filter::IsOwned && !Filter::IsConstructing); //Search a worker to build buildings

				if (builder && builder->getID() != knowledgeBase->getScout())
					processingBuildingOrder->setBuilder(builder->getID());
			}
		}
		else
		{
			if (building != nullptr)
			{
				utility->getBuildingOrdersManager()->removeBuildingOrder(processingBuildingOrder->getID());
				processingBuildingOrder = nullptr;
			}
			else
			{
				if (builder->exists() && builder->getHitPoints() > 0 && !builder->isConstructing())
				{
					TilePosition targetBuildLocation = Broodwar->getBuildLocation(unitType, builder->getTilePosition(), 25);

					if (Broodwar->canBuildHere(targetBuildLocation, unitType, builder))
						builder->build(unitType, targetBuildLocation);
				}
				else
					if (builder->exists() && builder->getHitPoints() > 0 && builder->isConstructing())
					{
						Unit target = builder->getOrderTarget();

						if (target != nullptr && target->getType() == unitType && target->getHitPoints() > 0)
						{
							processingBuildingOrder->setBuilding(target->getID());
						}
					}
			}
		}	
	}

	//Remove completed orders
	unordered_map<int, BuildingOrder*> buildingOrders = utility->getBuildingOrdersManager()->getBuildingOrders();

	for (auto it = buildingOrders.begin(); it != buildingOrders.end(); it++) //Check if there are completed orders
	{
		BuildingOrder* buildingOrder = (*it).second;
		int orderSize = buildingOrder->getOrderSize();

		bool completed = false;

		for (int i = 0; i < orderSize && !completed; i++)
		{
			Unit building = Broodwar->getUnit(buildingOrder->getBuilding(i));
			Unit builder = Broodwar->getUnit(buildingOrder->getBuilder(i));

			completed = utility->getBuildingOrdersManager()->deleteBuildingOrder(buildingOrder->getID());

			if (building != nullptr && !building->isCompleted() && (!builder->exists() || builder->getHitPoints() <= 0)) //Check if a building is uncompleted and the builder is dead
			{
				Unit commandCenter = Broodwar->getUnit(knowledgeBase->getCommandCenter());
				UnitType unitType = building->getType();

				if (commandCenter != NULL && commandCenter->exists() && commandCenter->getHitPoints() > 0 && Broodwar->self()->minerals() >= unitType.mineralPrice())
				{
					Unit anotherBuilder = commandCenter->getClosestUnit(Filter::GetType == unitType.whatBuilds().first &&
						(Filter::IsIdle || Filter::IsGatheringMinerals) &&
						Filter::IsOwned && !Filter::IsConstructing); //Search a worker to build buildings

					if (anotherBuilder && anotherBuilder->getID() != knowledgeBase->getScout())
						if (anotherBuilder->rightClick(building))
							buildingOrder->setBuilder(anotherBuilder->getID(), i);
				}
			}
		}
	}

	//Remove destroyed buildings
	set< int > barracks = knowledgeBase->getBarracks();

	for (auto it = barracks.begin(); it != barracks.end(); it++)
	{
		Unit currentBarrack = Broodwar->getUnit((*it));

		if (!currentBarrack->exists() || currentBarrack->getHitPoints() <= 0)
			knowledgeBase->removeBarrack((*it));
	}
}
