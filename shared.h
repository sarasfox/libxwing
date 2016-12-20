#pragma once
#include <functional>
#include <string>
#include <stdint.h>



// Faction
enum class Faction {
  None   = 0,
  Empire = 1,
  Rebel  = 2,
  Scum   = 4,
  All    = 7
};
Faction operator|(Faction a, Faction b);
std::string FactionToString(Faction f);
Faction     StringToFaction(std::string f);



// Base Size
enum class BaseSize {
  None  = 0,
  Small = 1,
  Large = 2,
  All   = 3
};
BaseSize operator|(BaseSize a, BaseSize b);



// Actions
enum class Act : uint32_t {
  None       = 0x0000,
  Focus      = 0x0001,
  TargetLock = 0x0002,
  BarrelRoll = 0x0004,
  Boost      = 0x0008,
  Evade      = 0x0010,
  Cloak      = 0x0020,
  SLAM       = 0x0040,
  RotateArc  = 0x0080
};
Act operator|(Act a, Act b);
Act operator&(Act a, Act b);
Act operator+(Act a, Act b);
Act operator-(Act a, Act b);
//Act operator+=(Act a, Act b);
//Act operator-=(Act a, Act b);

std::string ActToString(Act a);
std::string GetActGlyph(Act a);
void ForEachAction(Act actions, std::function<void(Act)>f);



// Upgrades
enum class Upg {
  Modification      =  1,
  Elite             =  2,
  Torpedo           =  3,
  Astromech         =  4,
  Turret            =  5,
  Missile           =  6,
  Title             =  7,
  Crew              =  8,
  Cannon            =  9,
  Bomb              = 10,
  System            = 11,
  SalvagedAstromech = 12,
  Illicit           = 13,
  Tech              = 14,
};
std::string UpgToString(Upg u);
std::string GetUpgGlyph(Upg u);
