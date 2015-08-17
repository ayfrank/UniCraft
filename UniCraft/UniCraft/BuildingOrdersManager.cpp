#include "BuildingOrdersManager.h"


BuildingOrdersManager::BuildingOrdersManager(KnowledgeBase* knowledgeBase)
{
	this->knowledgeBase = knowledgeBase;
	orderNumber = 0;
}


BuildingOrdersManager::~BuildingOrdersManager()
{
}

int BuildingOrdersManager::insertBuildingOrder(UnitType unitType, Priority priority)
{
	vector<UnitType> unitTypes;
	unitTypes.push_back(unitType);
	
	return insertBuildingOrder(unitTypes, priority);
}

int BuildingOrdersManager::insertBuildingOrder(vector<UnitType> unitsType, Priority priority)
{
	BuildingOrder* buildingOrder = new BuildingOrder(orderNumber, unitsType, priority);

	buildingOrders.insert({ orderNumber, buildingOrder });
	insertIntoPriorityQueue(buildingOrder, priority);

	return orderNumber++;
}
void BuildingOrdersManager::insertIntoPriorityQueue(BuildingOrder* buildingOrder, Priority priority)
{
	if (priorityQueue.empty())
		priorityQueue.push_back(buildingOrder);
	else
	{
		bool inserted = false;

		for (auto it = priorityQueue.begin(); it != priorityQueue.end() && inserted == false; it++)
			if ((*it)->getPriority() < priority)
			{
				priorityQueue.insert(it, buildingOrder);
				inserted = true;
			}

		if (!inserted)
			priorityQueue.push_back(buildingOrder);
	}
}

bool BuildingOrdersManager::searchBuildingOrder(int orderID)
{
	if (buildingOrders.find(orderID) == buildingOrders.end())
		return false;

	return true;
}

BuildingOrder* BuildingOrdersManager::getBuildingOrder()
{
	if (priorityQueue.size() > 0)
		return priorityQueue.front();

	return nullptr;
}

bool BuildingOrdersManager::removeBuildingOrder(int orderID)
{
	auto it = buildingOrders.find(orderID);

	if (it != buildingOrders.end())
	{
		BuildingOrder* buildingOrder = (*it).second;

		vector<int> buildings = buildingOrder->getBuildings();

		for (unsigned int i = 0; i < buildings.size(); i++)
		{
			Unit building = Broodwar->getUnit(buildings[i]);
			if (building != nullptr && building->getHitPoints() > 0)
				buildingOrder->insertProcessingBuilding(buildings[i]);
		}

		if (buildingOrder->allOrdersAreStarted())
		{
			for (auto it = priorityQueue.begin(); it != priorityQueue.end(); it++)
				if ((*it)->getID() == orderID)
				{
					priorityQueue.erase(it);
					break;
				}

			return true;
		}
	}

	return false;
}

bool BuildingOrdersManager::deleteBuildingOrder(int orderID)
{
	auto it = buildingOrders.find(orderID);

	if (it != buildingOrders.end())
	{
		BuildingOrder* buildingOrder = (*it).second;

		vector<int> buildings = buildingOrder->getBuildings();

		for (unsigned int i = 0; i < buildings.size(); i++)
		{
			Unit building = Broodwar->getUnit(buildings[i]);

			if (building != nullptr && building->isCompleted() || building != nullptr && !building->exists())
			{
				buildingOrder->insertCompletedBuilding(buildings[i]);

				if (building->getType() == UnitTypes::Terran_Barracks && building->getHitPoints() > 0)
					knowledgeBase->addBarrack(buildings[i]);
				else
					if (building->getType() == UnitTypes::Terran_Command_Center && building->getHitPoints() > 0)
						knowledgeBase->setCommandCenter(buildings[i]);
			}
		}

		if (buildingOrder->isCompleted())
		{
			buildingOrders.erase(it);
			delete buildingOrder;
			return true;
		}
	}
	
	return false;
}

unordered_map<int, BuildingOrder*> BuildingOrdersManager::getBuildingOrders()
{
	return buildingOrders;
}