#pragma once

#include <BWAPI.h>
#include <vector>

using namespace BWAPI;
using namespace std;

enum Priority { LOW, MID, HIGH };

class BuildingOrder
{
	public:
		BuildingOrder(int, vector<UnitType>, Priority);
		~BuildingOrder();

		Priority getPriority();
		UnitType getUnitType();
		int getBuilder();
		int getBuilding();
		int getID();

		int getBuilding(int);
		int getBuilder(int);

		int getOrderSize();

		void setBuilder(int);
		void setBuilding(int);

		void setBuilder(int, int);
		void setBuilding(int, int);

		bool isCompleted();
		bool allOrdersAreStarted();

		vector<int> getBuildings();

		void insertProcessingBuilding(int);
		void insertCompletedBuilding(int);

		int currentOrder;

	private:
		int orderID;
		vector<UnitType> unitsType;
		vector<int> builders;
		vector<int> buildings;
		Priority priority;

		set<int> processingBuildings;
		set<int> completedBuildings;
};

