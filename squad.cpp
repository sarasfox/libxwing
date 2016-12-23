#include "squad.h"
#include "./json/json.h"
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



bool Squad::Verify() {
  bool ret = true;
  int cost = 0;
  for(Pilot &p : this->GetPilots()) {
    cost += p.GetModCost();
    // check faction
    if(p.GetFaction() != this->GetFaction()) {
      printf("ERROR: Squad is %s but pilot '%s' is %s\n",
	     FactionToString(this->GetFaction()).c_str(), p.GetPilotName().c_str(), FactionToString(p.GetFaction()).c_str());
      ret = false;
    }

    // check upgrades
    std::vector<Upg> openSlots = p.GetModPossibleUpgrades();
    for(Upgrade &u : p.GetAppliedUpgrades()) {
      if(std::find(openSlots.begin(), openSlots.end(), u.GetType()) == openSlots.end()) {
	printf("ERROR: No %s slot for upgrade '%s'\n", UpgToString(u.GetType()).c_str(), u.GetUpgradeName().c_str());
	ret = false;
      }
      //if(u.
    }

  }

  // check cost
  if(cost > 100) {
    printf("ERROR: Squad cost is %d\n", cost);
    ret = false;
  }
  return ret;
}



std::string         Squad::GetName()        { return this->name; }
std::string         Squad::GetDescription() { return this->description; }
Faction             Squad::GetFaction()     { return this->faction; }
std::vector<Pilot>& Squad::GetPilots()      { return this->pilots; }

void Squad::Dump() {
  printf("DUMP\n");
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
