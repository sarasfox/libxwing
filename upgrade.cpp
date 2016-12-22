#include "upgrade.h"
#include "shared.h"
#include <algorithm>
#include <exception>
#include <list>



Upgrade Upgrade::GetUpgrade(std::string category, std::string name) {
  for(Upgrade &us : Upgrade::upgrades) {
    if((UpgToString(us.GetType()) == category) && (us.GetUpgradeNameXws() == name)) {
      return us;
    }
  }
  throw std::invalid_argument("Unknown upgrade (" + category + "/" + name + ")");
}



void Upgrade::SanityCheck() {
  typedef std::tuple<std::string, std::string> Entry;
  std::list<Entry> entries;
  std::list<Entry> dupes;
  int counter=0;
  printf("Checking Upgrades");
  for(Upgrade u : upgrades) {
    counter++;
    Entry e = Entry{UpgToString(u.GetType()), u.GetUpgradeNameXws() };
    if(std::find(entries.begin(), entries.end(), e) == entries.end()) {
      printf("."); fflush(stdout);
    } else {
      dupes.push_back(e);
      printf("X"); fflush(stdout);
    }
    entries.push_back(e);
  }
  printf("DONE\n");
  printf("Upgrades: %zu\n", entries.size());
  printf("Dupes: %zu\n", dupes.size());
  if(dupes.size()) {
    for(Entry e : dupes) {
      printf("  %s - %s\n", std::get<0>(e).c_str(), std::get<1>(e).c_str());
    }
  }
}



Upgrade::Upgrade(std::string  n,
		 std::string  ns,
		 std::string  nx,
		 Upg          typ,
		 int8_t       cst,
		 bool         uni,
		 bool         lim,
		 Modifiers    um,
		 Restrictions rest)
  : name(n), nameShort(ns), nameXws(nx), type(typ), cost(cst),
    isUnique(uni), isLimited(lim), modifier(um), restriction(rest),
    isEnabled(true) { }

std::string  Upgrade::GetUpgradeName()      { return this->name; }
std::string  Upgrade::GetUpgradeNameShort() { return this->nameShort; }
std::string  Upgrade::GetUpgradeNameXws()   { return this->nameXws; }
Upg          Upgrade::GetType()             { return this->type; }
int8_t       Upgrade::GetCost()             { return this->cost; }
bool         Upgrade::GetIsUnique()         { return this->isUnique; }
bool         Upgrade::GetIsLimited()        { return this->isLimited; }
Modifiers    Upgrade::GetModifier()         { return this->modifier; }
Restrictions Upgrade::GetRestriction()     { return this->restriction; }

void Upgrade::Enable()       { this->isEnabled = true; }
void Upgrade::Disable()      { this->isEnabled = false; }
bool Upgrade::GetIsEnabled() { return this->isEnabled; }
