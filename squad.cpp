#include "squad.h"
#include "./json/json.h"
#include <algorithm>
#include <fstream>

Squad::Squad(std::string xwsFile) {
  Json::Value root;
  try {
    std::ifstream xws(xwsFile, std::ifstream::binary);
    xws >> root;
  }
  catch(...) {
    throw std::invalid_argument(xwsFile);
  }

  this->name        = root.get("name", "").asString();
  this->description = root.get("listdesc", "").asString();
  this->faction     = StringToFaction(root.get("faction", "").asString());

  for(int i=0; i<root["pilots"].size(); i++) {
    Json::Value jsonPilot = root["pilots"][i];

    std::string pilotname = jsonPilot.get("name", "").asString();
    std::string shipname = jsonPilot.get("ship", "").asString();
    Pilot p = Pilot::GetPilot(pilotname, FactionToString(this->faction), shipname);

    Json::Value jsu = jsonPilot["upgrades"];
    for(Json::ValueIterator iCat = jsu.begin(); iCat != jsu.end() ; iCat++ ) {
      std::string category = iCat.key().asString().c_str();
      Json::Value jsCat = jsu[category];
      for(int i=0; i<jsCat.size(); i++) {
	std::string upgrade = jsCat[i].asString();
	Upgrade u = Upgrade::GetUpgrade(category, upgrade);
	p.ApplyUpgrade(u);
      }
    }
    this->pilots.push_back(p);
  }
}



std::vector<std::string> Squad::Verify() {
  std::vector<std::string> ret;
  int cost = 0;
  std::vector<std::string> uniques;
  for(Pilot &p : this->GetPilots()) {
    cost += p.GetModCost();

    // unique
    if(p.GetIsUnique()) {
      std::string n = p.GetPilotName();
      if(std::find(uniques.begin(), uniques.end(), n) == uniques.end()) {
	uniques.push_back(n);
      } else {
	ret.push_back("Multiple uses of unique character " + n);
      }
    }

    // check faction
    if(p.GetFaction() != this->GetFaction()) {
      ret.push_back("Squad is " + FactionToString(this->GetFaction()) + " but pilot '" + p.GetPilotName() + "' is " + FactionToString(p.GetFaction()));
    }

    // check upgrades
    std::vector<std::string> limiteds; 
    std::vector<Upg> openSlots = p.GetModPossibleUpgrades();
    for(Upgrade &u : p.GetAppliedUpgrades()) {

      // unique
      if(u.GetIsUnique()) {
	std::string n = u.GetUpgradeName();
	if(std::find(uniques.begin(), uniques.end(), n) == uniques.end()) {
	  uniques.push_back(n);
	} else {
	  ret.push_back("Multiple uses of unique character " + n);
	}
      }

      // limited
      if(u.GetIsLimited()) {
	std::string n = u.GetUpgradeName();
	if(std::find(limiteds.begin(), limiteds.end(), n) == limiteds.end()) {
	  limiteds.push_back(n);
	} else {
	  ret.push_back("Multiple uses of limited upgrade " + n + " on " + p.GetPilotName());
	}
      }

      // have slot
      if(std::find(openSlots.begin(), openSlots.end(), u.GetType()) == openSlots.end()) {
	ret.push_back("No " + UpgToString(u.GetType()) + " slot for upgrade '" + u.GetUpgradeName() + "'\n");
      }

      // check upgrade restrictions
      auto errs = u.GetRestrictionCheck()(p);
      for(std::string e : errs) {
	ret.push_back(e);
      }
    }
  }

  // check cost
  if(cost > 100) {
    ret.push_back("Squad cost is " + std::to_string(cost));
  }
  return ret;
}



std::string         Squad::GetName()        { return this->name; }
std::string         Squad::GetDescription() { return this->description; }
Faction             Squad::GetFaction()     { return this->faction; }
std::vector<Pilot>& Squad::GetPilots()      { return this->pilots; }

void Squad::Dump() {
  bool fancy = true;
  if(fancy) {
    //              |
    printf("\e[1;37m\"%s\" [%s]\n", this->name.c_str(), FactionToString(this->faction).c_str());
    if(!this->description.empty()) {
      printf("%s\n", this->description.c_str());
    }

  }
  else {
    printf("Name:        '%s'\n", this->name.c_str());
    printf("Description: '%s'\n", this->description.c_str());
    printf("Faction:     %s\n",   FactionToString(this->faction).c_str());
  }
  for(auto p : this->pilots) {
    printf("\n");
    p.Dump();
  }
}
