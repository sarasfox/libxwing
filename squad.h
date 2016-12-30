#pragma once
#include "shared.h"
#include "pilot.h"
#include <vector>


class Squad {
 public:
  Squad(std::string xwsFile);
  std::vector<std::string> Verify();
  std::string GetName();
  std::string GetDescription();
  Faction     GetFaction();
  std::vector<Pilot>& GetPilots();

  void Dump();

 private:
  std::string name;
  std::string description;
  Faction faction;
  std::vector<Pilot> pilots;
};
