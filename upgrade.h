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

class Upgrade {
 public:
  static Upgrade GetUpgrade(std::string category, std::string name);
  static void SanityCheck();

  std::string GetUpgradeName();
  std::string GetUpgradeNameShort();
  std::string GetUpgradeNameXws();

  Upg        GetType();
  int8_t     GetCost();
  bool       GetIsUnique();
  bool       GetIsLimited();
  Modifiers GetModifier();

  void Enable();
  void Disable();
  bool GetIsEnabled();

  void Dump();

 private:
  std::string name;
  std::string nameShort;
  std::string nameXws;
  Upg         type;
  int8_t      cost;
  bool        isUnique;
  bool        isLimited;
  Modifiers   modifier;

  bool isEnabled;

  static std::list<Upgrade> upgrades;

  Upgrade(std::string n,
	  std::string ns,
	  std::string nx,
	  Upg         typ,
	  int8_t      cst,
	  bool        uni,
	  bool        lim,
	  Modifiers   um);
};
