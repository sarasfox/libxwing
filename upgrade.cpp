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

std::list<Upgrade> Upgrade::GetAllUpgrades() { return Upgrade::upgrades; }

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



Upgrade::Upgrade(std::string      n,
                 std::string      ns,
                 std::string      nx,
                 Upg              typ,
                 std::vector<Upg> slts,
                 int8_t           cst,
                 bool             uni,
                 bool             lim,
                 Modifiers        um,
                 RestrictionCheck rc,
                 std::string      txt)
  : isEnabled(true),name(n), nameShort(ns), nameXws(nx), type(typ), slots(slts), cost(cst),
    isUnique(uni), isLimited(lim), modifier(um), restrictionCheck(rc), text(txt) { }

std::string      Upgrade::GetUpgradeName()      const { return this->name; }
std::string      Upgrade::GetUpgradeNameShort() const { return this->nameShort; }
std::string      Upgrade::GetUpgradeNameXws()   const { return this->nameXws; }
Upg              Upgrade::GetType()             const { return this->type; }
std::vector<Upg> Upgrade::GetSlots()            const { return this->slots; }
int8_t           Upgrade::GetCost()             const { return this->cost; }
bool             Upgrade::GetIsUnique()         const { return this->isUnique; }
bool             Upgrade::GetIsLimited()        const { return this->isLimited; }
Modifiers        Upgrade::GetModifier()         const { return this->modifier; }
RestrictionCheck Upgrade::GetRestrictionCheck() const { return this->restrictionCheck; }

void Upgrade::Enable()       { this->isEnabled = true; }
void Upgrade::Disable()      { this->isEnabled = false; }
bool Upgrade::GetIsEnabled() const { return this->isEnabled; }
