#include "pilot.h"
#include "shared.h"
#include <algorithm>
#include <exception>
#include <list>



Pilot Pilot::GetPilot(std::string pilot, std::string faction, std::string ship) {
  for(Pilot &ps : Pilot::pilots) {
    if((ps.GetPilotNameXws() == pilot) && (ps.GetFaction() == StringToFaction(faction)) && (ps.GetShipNameXws() == ship)) {
      return ps;
    }
  }
  throw std::invalid_argument("Unknown ship (" + pilot + "/" + faction + "/" + ship + ")");
}

std::list<Pilot> Pilot::GetAllPilots() { return Pilot::pilots; }

void Pilot::SanityCheck() {
  typedef std::tuple<std::string, std::string, std::string> Entry;
  std::list<Entry> entries;
  std::list<Entry> dupes;
  int counter=0;
  printf("Checking Pilots");
  for(Pilot p : pilots) {
    counter++;
    Entry e = Entry{p.GetPilotNameXws(), FactionToString(p.GetFaction()), p.GetShipNameXws() };
    if(std::find(entries.begin(), entries.end(), e) == entries.end()) {
      printf("."); fflush(stdout);
    } else {
      dupes.push_back(e);
      printf("X"); fflush(stdout);
    }
    entries.push_back(e);
  }
  printf("DONE\n");
  printf("Pilots: %zu\n", entries.size());
  printf("Dupes: %zu\n", dupes.size());
  if(dupes.size()) {
    for(Entry e : dupes) {
      printf("  %s - %s - %s\n", std::get<0>(e).c_str(), std::get<1>(e).c_str(), std::get<2>(e).c_str());
    }
  }
}



Pilot::Pilot(Faction     fact,
             BaseSize    bs,
             std::string name,
             std::string snam,
             std::string xnam,
             std::string ship,
             std::string xshi,
             std::string gly,
             Maneuvers   man,
             bool        uni,
             int8_t      ps,
             int8_t      at,
             int8_t      ag,
             int8_t      hu,
             int8_t      sh,
             int8_t      cs,
             Act         ac,
             std::vector<Upg> up)
  : faction(fact), baseSize(bs),
    pilotName(name), pilotNameShort(snam), pilotNameXws(xnam),
    shipName(ship), shipNameXws(xshi), shipGlyph(gly), maneuvers(man),
    isUnique(uni), skill(ps),
    attack(at), agility(ag), hull(hu), shield(sh), cost(cs),
    actions(ac), possibleUpgrades(up),
    isEnabled(true), shieldHits(0), hullHits(0) { }

Faction     Pilot::GetFaction()        const { return this->faction; }
BaseSize    Pilot::GetBaseSize()       const { return this->baseSize; }
std::string Pilot::GetPilotName()      const { return this->pilotName; }
std::string Pilot::GetPilotNameShort() const { return this->pilotNameShort; }
std::string Pilot::GetPilotNameXws()   const { return this->pilotNameXws; }
std::string Pilot::GetShipName()       const { return this->shipName; }
std::string Pilot::GetShipNameXws()    const { return this->shipNameXws; }
std::string Pilot::GetShipGlyph()      const { return this->shipGlyph; }
Maneuvers   Pilot::GetManeuvers()      const { return this->maneuvers; }
bool        Pilot::GetIsUnique()       const { return this->isUnique; }

int8_t Pilot::GetNatSkill()   const { return this->skill; }
int8_t Pilot::GetNatAttack()  const { return this->attack; }
int8_t Pilot::GetNatAgility() const { return this->agility; }
int8_t Pilot::GetNatHull()    const { return this->hull; }
int8_t Pilot::GetNatShield()  const { return this->shield; }
int8_t Pilot::GetNatCost()    const { return this->cost; }
Act    Pilot::GetNatActions() const { return this->actions; }
std::vector<Upg> Pilot::GetNatPossibleUpgrades() const { return this->possibleUpgrades; }

int8_t Pilot::GetModSkill() const {
  int8_t skill = this->skill;
  for(Upgrade u : this->appliedUpgrades) {
    if(u.GetIsEnabled()) {
      skill += u.GetModifier().skill(*this);
    }
  }
  return skill;
}
int8_t Pilot::GetModAttack() const {
  int8_t attack = this->attack;
  for(Upgrade u : this->appliedUpgrades) {
    if(u.GetIsEnabled()) {
      attack += u.GetModifier().attack(*this);
    }
  }
  return attack;
}
int8_t Pilot::GetModAgility() const {
  int8_t agility = this->agility;
  for(Upgrade u : this->appliedUpgrades) {
    if(u.GetIsEnabled()) {
      agility += u.GetModifier().agility(*this);
    }
  }
  return agility;
}
int8_t Pilot::GetModHull() const {
  int8_t hull = this->hull;
  for(Upgrade u : this->appliedUpgrades) {
    if(u.GetIsEnabled()) {
      hull += u.GetModifier().hull(*this);
    }
  }
  return hull;
}
int8_t Pilot::GetModShield() const {
  int8_t shield = this->shield;
  for(Upgrade u : this->appliedUpgrades) {
    if(u.GetIsEnabled()) {
      shield += u.GetModifier().shield(*this);
    }
  }
  return shield;
}
int8_t Pilot::GetModCost() const {
  int8_t cost = this->cost;
  for(Upgrade u : this->appliedUpgrades) {
    cost += u.GetCost();
    cost += u.GetModifier().cost(*this);
  }
  return cost;
}
Act Pilot::GetModActions() const {
  Act act = this->actions;
  for(Upgrade u : this->appliedUpgrades) {
    if(u.GetIsEnabled()) {
      act = act + u.GetModifier().addAct(*this);
      act = act - u.GetModifier().remAct(*this);
    }
  }
  return act;
}

std::vector<Upg> Pilot::GetModPossibleUpgrades() const {
  std::vector<Upg> upg = this->possibleUpgrades;
  for(Upgrade u : this->appliedUpgrades) {
    if(u.GetIsEnabled()) {
      for(Upg x : u.GetModifier().addUpg(*this)) { upg.push_back(x); }
      for(Upg x : u.GetModifier().remUpg(*this)) { upg.erase(std::remove(upg.begin(), upg.end(), x), upg.end()); }
    }
  }
  return upg;
}


std::vector<Upgrade> Pilot::GetAppliedUpgrades() const { return this->appliedUpgrades; }

bool   Pilot::GetIsEnabled()  const { return this->isEnabled; }
int8_t Pilot::GetCurShield()  const { return this->GetModShield() - this->shieldHits; }
int8_t Pilot::GetCurHull()    const { return this->GetModHull() - this->hullHits; }
int8_t Pilot::GetShieldHits() const { return this->shieldHits; }
int8_t Pilot::GetHullHits()   const { return this->hullHits; }

void Pilot::Enable()   { this->isEnabled = true; }
void Pilot::Disable()  { this->isEnabled = false; }
void Pilot::ShieldUp() { if(this->shieldHits > 0) this->shieldHits--; }
void Pilot::ShieldDn() { if(this->shieldHits < this->GetModShield()) this->shieldHits++; }
void Pilot::HullUp()   { if(this->hullHits > 0) this->hullHits--; }
void Pilot::HullDn()   { if(this->hullHits < this->GetModHull()) this->hullHits++; }


void Pilot::ApplyUpgrade(Upgrade u) {
  this->appliedUpgrades.push_back(u);
}



#define NORMAL "\x1B[0m"
#define GRAY   "\e[0;37m"
#define WHITE  "\e[1;37m"
#define BROWN  "\e[0;33m"
#define RED    "\e[1;31m"
#define GREEN  "\e[1;32m"
#define YELLOW "\e[1;33m"
#define BLUE   "\e[1;34m"


bool FindManeuver(Maneuvers maneuvers, uint8_t speed, Bearing bearing, Maneuver &maneuver) {
  for(auto m : maneuvers) {
    if((m.speed == speed) && (m.bearing == bearing)) {
      maneuver = m;
      return true;
    }
  }
  return false;
}

std::string GetDifficultyColor(Difficulty d) {
  switch(d) {
  case Difficulty::Green: return GREEN;
  case Difficulty::White: return WHITE;
  case Difficulty::Red:   return RED;
  }
}

std::string GetBearingSymbol(Bearing b) {
  switch(b) {
  case Bearing::LTurn:      return "↰";
  case Bearing::LBank:      return "↖";
  case Bearing::Straight:   return "↑";
  case Bearing::Stationary: return "■";
  case Bearing::RBank:      return "↗";
  case Bearing::RTurn:      return "↱";
  case Bearing::KTurn:      return "K";
  case Bearing::LSloop:     return "↖";
  case Bearing::RSloop:     return "↗";
  case Bearing::LTroll:     return "↰";
  case Bearing::RTroll:     return "↱";
  default:                  return "?";
  }
}


void Pilot::Dump() {
  bool fancy = true;
  if(fancy) {
    //      C  C |co C   |pi  |sh
    printf("%s[%s%hhd%s] %s - %s\n",
	   WHITE,GRAY,this->GetModCost(),WHITE, this->pilotName.c_str(), this->shipName.c_str());
    
    //      C |sk C    C |attC /C |agi  /C |hulC /C |sh C

    // skill
    printf("%s%hhu", BROWN, this->GetNatSkill());
    if(this->GetNatSkill() != this->GetModSkill()) {
      printf("(%hhu)", this->GetModSkill());
    }
    printf("%s - ", WHITE);

    // attack
    printf("%s%hhu", RED, this->GetNatAttack());
    if(this->GetNatAttack() != this->GetModAttack()) {
      printf("(%hhu)", this->GetModAttack());
    }
    printf("%s/", WHITE);

    // agility
    printf("%s%hhu", GREEN, this->GetNatAgility());
    if(this->GetNatAgility() != this->GetModAgility()) {
      printf("(%hhu)", this->GetModAgility());
    }
    printf("%s/", WHITE);

    // hull
    printf("%s%hhu", YELLOW, this->GetNatHull());
    if(this->GetNatHull() != this->GetModHull()) {
      printf("(%hhu)", this->GetModHull());
    }
    printf("%s/", WHITE);

    // shield
    printf("%s%hhu", BLUE, this->GetNatShield());
    if(this->GetNatShield() != this->GetModShield()) {
      printf("(%hhu)", this->GetModShield());
    }
    printf("%s - ", WHITE);

    ForEachAction(this->GetModActions(), [](Act a) {printf("[%s]", ActToString(a).c_str());});
    printf(" - ");
    for(Upg u : this->GetModPossibleUpgrades()) {
      printf("[%s]", UpgToString(u).c_str());
    }
    printf("\nUpgrades:");
    for(auto u : this->GetAppliedUpgrades()) {
      printf(" [%s]", u.GetUpgradeName().c_str());
    }
    printf(NORMAL"\n");

    // draw the maneuver chart
    Maneuvers ms = this->GetManeuvers();
    int8_t min = 10;
    int8_t max = -10;
    for(auto a : ms) { if(a.speed > max) {max = a.speed;} if(a.speed < min) {min=a.speed;} }

    Maneuver m;
    for(int i=max; i>=min; i--) {
      printf(WHITE"%2d|", i);

      // standard maneuvers
      for(Bearing b : {Bearing::LTurn, Bearing::LBank, (i==0) ? Bearing::Stationary : Bearing::Straight, Bearing::RBank, Bearing::RTurn}) {
        if(FindManeuver(ms, i, b, m)) {
          printf(" %s%s%s", GetDifficultyColor(m.difficulty).c_str(), GetBearingSymbol(m.bearing).c_str(), NORMAL);
        } else {
          printf("  ");
        }
      }

      // special maneuvers
      for(Bearing b : {Bearing::KTurn, Bearing::LSloop, Bearing::RSloop, Bearing::LTroll, Bearing::RTroll}) {
        if(FindManeuver(ms, i, b, m)) {
          printf(" %s%s%s", GetDifficultyColor(m.difficulty).c_str(), GetBearingSymbol(m.bearing).c_str(), NORMAL);
        }
      }

      printf("\n");
    }

  }
  else {
    /*
    printf("Name:     %s [%s]\n", this->pilotName.c_str(), this->pilotNameXws.c_str());
    printf("Ship:     %s [%s]\n", this->shipName.c_str(), this->shipNameXws.c_str());
    //printf("glyph:    %s\n",      this->shipGlyph.c_str());
    printf("skill:    %hhd\n",    this->skill);
    printf("attack:   %hhd\n",    this->attack);
    printf("agility:  %hhd\n",    this->agility);
    printf("hull:     %hhd\n",    this->hull);
    printf("shield:   %hhd\n",    this->shield);
    printf("cost:     %hhd\n",    this->cost);

    printf("actions: ");
    //for(int i=0; i<this->actions.size(); i++) {
    //  printf(" %s", Actions[this->actions[i]].Name.c_str());
    //}
    printf("\n");
    */
  }
}
