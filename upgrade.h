#pragma once
#include "shared.h"
#include <list>
#include <string>
#include <vector>



class Pilot;
typedef std::function<int8_t          (const Pilot&)> SModifier;
typedef std::function<Act             (const Pilot&)> AModifier;
typedef std::function<std::vector<Upg>(const Pilot&)> UModifier;

struct Modifiers {
  SModifier skill;
  SModifier attack;
  SModifier agility;
  SModifier hull;
  SModifier shield;
  SModifier cost;
  AModifier addAct;
  AModifier remAct;
  UModifier addUpg;
  UModifier remUpg;
};



typedef std::function<std::vector<std::string>(const Pilot&)> RestrictionCheck;



class Upgrade {
 public:
  static Upgrade GetUpgrade(std::string category, std::string name);
  static void SanityCheck();

  std::string GetUpgradeName()      const;
  std::string GetUpgradeNameShort() const;
  std::string GetUpgradeNameXws()   const;

  Upg              GetType()  const;
  std::vector<Upg> GetSlots() const;
  int8_t           GetCost()  const;
  bool             GetIsUnique() const;
  bool             GetIsLimited() const;
  Modifiers        GetModifier() const;
  RestrictionCheck GetRestrictionCheck() const;

  void Enable();
  void Disable();
  bool GetIsEnabled() const;

  void Dump();

 private:
  bool             isEnabled;
  std::string      name;
  std::string      nameShort;
  std::string      nameXws;
  Upg              type;
  std::vector<Upg> slots;
  int8_t           cost;
  bool             isUnique;
  bool             isLimited;
  Modifiers        modifier;
  RestrictionCheck restrictionCheck;
  std::string      text;

  static std::list<Upgrade> upgrades;

  Upgrade(std::string       n,
          std::string       ns,
          std::string       nx,
          Upg               typ,
          std::vector<Upg>  slt,
          int8_t            cst,
          bool              uni,
          bool              lim,
          Modifiers         um,
          RestrictionCheck  rc,
          std::string       txt);
};
