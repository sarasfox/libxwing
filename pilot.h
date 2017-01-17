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
  static std::list<Pilot> GetAllPilots();
  static void SanityCheck();

  Faction     GetFaction()        const;
  BaseSize    GetBaseSize()       const;
  std::string GetPilotName()      const;
  std::string GetPilotNameShort() const;
  std::string GetPilotNameXws()   const;
  std::string GetShipName()       const;
  std::string GetShipNameXws()    const;
  std::string GetShipGlyph()      const;
  bool        GetHasAbility()     const;
  std::string GetText()           const;
  Maneuvers   GetManeuvers()      const;
  bool        GetIsUnique()       const;

  int8_t GetNatSkill()   const;
  int8_t GetNatAttack()  const;
  int8_t GetNatAgility() const;
  int8_t GetNatHull()    const;
  int8_t GetNatShield()  const;
  int8_t GetNatCost()    const;
  Act    GetNatActions() const;
  std::vector<Upg> GetNatPossibleUpgrades() const;
  
  int8_t GetModSkill()   const;
  int8_t GetModAttack()  const;
  int8_t GetModAgility() const;
  int8_t GetModHull()    const;
  int8_t GetModShield()  const;
  int8_t GetModCost()    const;
  Act    GetModActions() const;
  std::vector<Upg> GetModPossibleUpgrades() const;

  std::vector<Upgrade> GetAppliedUpgrades() const;

  void ApplyUpgrade(Upgrade u);

  bool   GetIsEnabled()  const;
  int8_t GetCurShield()  const;
  int8_t GetCurHull()    const;
  int8_t GetShieldHits() const;
  int8_t GetHullHits()   const;

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
  bool        hasAbility;
  std::string text;
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
        std::vector<Upg> up,
        bool ha=false,
        std::string txt="");
};
