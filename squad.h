#pragma once
#include "shared.h"
#include "pilot.h"
#include <vector>


class Squad {
 public:
  Squad(std::string xwsFile);
  std::string GetName();
  std::vector<Pilot>& GetPilots();

  void Dump();

 private:
  std::string name;
  std::string description;
  std::string faction;
  std::vector<Pilot> pilots;
};
