#include "BuildingOrder.h"


BuildingOrder::BuildingOrder(int orderID, vector<UnitType> unitsType, Priority priority)
{
	this->orderID = orderID;
	this->unitsType = unitsType;
	this->priority = priority;

	for (unsigned int i = 0; i < unitsType.size(); i++)
	{
		buildings.push_back(-1);
		builders.push_back(-1);
	}
	currentOrder = 0;
}

BuildingOrder::~BuildingOrder()
{
}

Priority BuildingOrder::getPriority()
{
	return priority;
}

UnitType BuildingOrder::getUnitType()
{
	return unitsType[currentOrder];
}

void BuildingOrder::setBuilder(int builder)
{
	builders[currentOrder] = builder;
}

int BuildingOrder::getBuilder()
{
	return builders[currentOrder];
}

int BuildingOrder::getBuilding()
{
	return buildings[currentOrder];
}


void BuildingOrder::setBuilding(int building)
{
	buildings[currentOrder] = building;
}

int BuildingOrder::getBuilding(int i)
{
	return buildings[i];
}

int BuildingOrder::getBuilder(int i)
{
	return builders[i];
}

void BuildingOrder::setBuilder(int builder, int i)
{
	builders[i] = builder;
}

void BuildingOrder::setBuilding(int building, int i)
{
	buildings[i] = building;
}

int BuildingOrder::getOrderSize()
{
	return buildings.size();
}

int BuildingOrder::getID()
{
	return orderID;
}

bool BuildingOrder::isCompleted()
{
	return completedBuildings.size() == buildings.size();
}

bool BuildingOrder::allOrdersAreStarted()
{
	return processingBuildings.size() == buildings.size();
}

vector<int> BuildingOrder::getBuildings()
{
	return buildings;
}

void BuildingOrder::insertProcessingBuilding(int buildingID)
{
	if (processingBuildings.find(buildingID) == processingBuildings.end())
		currentOrder++;

	processingBuildings.insert(buildingID);
}

void BuildingOrder::insertCompletedBuilding(int buildingID)
{
	completedBuildings.insert(buildingID);
}
