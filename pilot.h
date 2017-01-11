#pragma once
#include "shared.h"
#include "upgrade.h"
#include <string>
#include <list>
#include <vector>

struct PilotKey {
  std::string pilot;
  std::string faction;
  std::string ship;
};

enum class Bearing {
  LTurn,
  LBank,
  Straight,
  RBank,
  RTurn,
  KTurn,
  Stationary,
  LSloop,
  RSloop,
  LTroll,
  RTroll
};

enum class Difficulty {
  Green,
  White,
  Red
};

struct Maneuver {
  int8_t     speed;
  Bearing    bearing;
  Difficulty difficulty;
};

typedef std::vector<Maneuver> Maneuvers;
//class Maneuvers : public std::vector<Maneuver> {
//};


class Pilot {
public:
  static Pilot GetPilot(std::string pilot, std::string faction, std::string ship);
  static void SanityCheck();

  Faction     GetFaction();
  BaseSize    GetBaseSize();
  std::string GetPilotName();
  std::string GetPilotNameShort();
  std::string GetPilotNameXws();
  std::string GetShipName();
  std::string GetShipNameXws();
  std::string GetShipGlyph();
  Maneuvers   GetManeuvers();
  bool        GetIsUnique();


  int8_t GetNatSkill();
  int8_t GetNatAttack();
  int8_t GetNatAgility();
  int8_t GetNatHull();
  int8_t GetNatShield();
  int8_t GetNatCost();
  Act    GetNatActions();
  std::vector<Upg> GetNatPossibleUpgrades();
  
  int8_t GetModSkill();
  int8_t GetModAttack();
  int8_t GetModAgility();
  int8_t GetModHull();
  int8_t GetModShield();
  int8_t GetModCost();
  Act    GetModActions();
  std::vector<Upg> GetModPossibleUpgrades();

  std::vector<Upgrade>& GetAppliedUpgrades();

  void ApplyUpgrade(Upgrade u);

  bool   GetIsEnabled();
  int8_t GetCurShield();
  int8_t GetCurHull();
  int8_t GetShieldHits();
  int8_t GetHullHits();

  void Enable();
  void Disable();
  void ShieldUp();
  void ShieldDn();
  void HullUp();
  void HullDn();

  void Dump();

private:
  Faction faction;
  BaseSize baseSize;
  std::string pilotName;
  std::string pilotNameShort;
  std::string pilotNameXws;
  std::string shipName;
  std::string shipNameXws;
  std::string shipGlyph;
  Maneuvers   maneuvers;
  bool   isUnique;
  int8_t skill;
  int8_t attack;
  int8_t agility;
  int8_t hull;
  int8_t shield;
  int8_t cost;
  Act    actions;
  std::vector<Upg>     possibleUpgrades;
  std::vector<Upgrade> appliedUpgrades;

  bool   isEnabled;
  int8_t shieldHits;
  int8_t hullHits;

  static std::list<Pilot> pilots;

  Pilot(Faction     fac,
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
        std::vector<Upg> up);
};
