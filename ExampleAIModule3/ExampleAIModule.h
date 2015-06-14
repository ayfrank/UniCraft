#pragma once
#include <BWAPI.h>
#include <windows.h>
#include <BWTA.h>
#include <vector>
#include <set>
#include <vector>

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
  bool visited;
  int barracksCount;
  std::list< BWAPI::Unit > buildingGroup;
  std::set<int> grouped;
  int x, y;
  unsigned int chockepointToDefende;
  void sortChockepoints();
  bool sorted;
  std::vector< BWTA::Chokepoint* > sortedChockepoints;
  bool isMoreDistant(BWAPI::Position p1, BWAPI::Position p2);
};
