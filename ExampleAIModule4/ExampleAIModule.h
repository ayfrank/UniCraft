#pragma once
#include <BWAPI.h>
#include <windows.h>
#include <BWTA.h>

DWORD WINAPI AnalyzeThread();

// Remember not to use "Broodwar" in any global class constructor!

class ExampleAIModule : public BWAPI::AIModule
{
public:
	// Virtual functions for callbacks, leave these as they are.
	virtual void onStart();
	virtual void onEnd(bool isWinner);
	virtual void onFrame();
	virtual void onSendText(std::string text);
	virtual void onReceiveText(BWAPI::Player player, std::string text);
	virtual void onPlayerLeft(BWAPI::Player player);
	virtual void onNukeDetect(BWAPI::Position target);
	virtual void onUnitDiscover(BWAPI::Unit unit);
	virtual void onUnitEvade(BWAPI::Unit unit);
	virtual void onUnitShow(BWAPI::Unit unit);
	virtual void onUnitHide(BWAPI::Unit unit);
	virtual void onUnitCreate(BWAPI::Unit unit);
	virtual void onUnitDestroy(BWAPI::Unit unit);
	virtual void onUnitMorph(BWAPI::Unit unit);
	virtual void onUnitRenegade(BWAPI::Unit unit);
	virtual void onSaveGame(std::string gameName);
	virtual void onUnitComplete(BWAPI::Unit unit);
	// Everything below this line is safe to modify.

	void drawTerrainData();

    private:
	  int lastBaseVisited;
	  int scoutID;
	  int SCVCount;
	  bool lastDestinationReached;
	  bool visited;
	  const int DELTA_TILE = 100;
	  bool attacked;

	  int x, y;
	  int a, b;

	  BWAPI::Position startPosition;
	  std::vector< BWTA::BaseLocation* > baseLocations;
};
