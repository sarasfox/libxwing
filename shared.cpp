#include "shared.h"



// Faction
Faction operator|(Faction a, Faction b) {
  return static_cast<Faction>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

Faction operator&(Faction a, Faction b) {
  return static_cast<Faction>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}

std::string FactionToString(Faction f) {
  switch(f) {
  case Faction::Empire: return "imperial";
  case Faction::Rebel:  return "rebel";
  case Faction::Scum:   return "scum";
  case Faction::None:   return "";
  case Faction::All:    return "all";
  }
}

Faction StringToFaction(std::string f) {
  if     (f == "imperial") return Faction::Empire;
  else if(f == "rebel")    return Faction::Rebel;
  else if(f == "scum")     return Faction::Scum;
  else                     return Faction::None;
}



// Base Size
BaseSize operator|(BaseSize a, BaseSize b) {
  return static_cast<BaseSize>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

BaseSize operator&(BaseSize a, BaseSize b) {
  return static_cast<BaseSize>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}

std::string BaseSizeToString(BaseSize bs) {
  switch(bs) {
  case BaseSize::None:  return "none";
  case BaseSize::Small: return "small";
  case BaseSize::Large: return "large";
  case BaseSize::All:   return "all";
  default:              return "???";
  }
}


// Actions
Act operator|(Act a, Act b) {
  return static_cast<Act>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

Act operator&(Act a, Act b) {
  return static_cast<Act>(static_cast<uint32_t>(a) & static_cast<uint32_t>(b));
}

Act operator+(Act a, Act b) {
  return static_cast<Act>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

Act operator-(Act a, Act b) {
  return static_cast<Act>(static_cast<uint32_t>(a) & ~static_cast<uint32_t>(b));
}

//Act operator+=(Act a, Act b) {
//  Act sum = static_cast<Act>(static_cast<uint32_t>(a) + static_cast<uint32_t>(b));
//  printf("+= a:%d b:%d sum:%d\n", a, b, sum);
//  return sum;
//}

//Act operator-=(Act a, Act b) {
//  return static_cast<Act>(static_cast<uint32_t>(a) - static_cast<uint32_t>(b));
//}

std::string ActToString(Act a) {
  switch(a) {
  case Act::None:       return "";
  case Act::Focus:      return "Focus";
  case Act::TargetLock: return "TargetLock";
  case Act::BarrelRoll: return "BarrelRoll";
  case Act::Boost:      return "Boost";
  case Act::Evade:      return "Evade";
  case Act::Cloak:      return "Cloak";
  case Act::SLAM:       return "SLAM";
  case Act::RotateArc:  return "RotateArc";
  case Act::Coordinate: return "Coordinate";
  default:              return "???";
  }
}

std::string GetActGlyph(Act a) {
  switch(a) {
  case Act::Focus:      return "f";
  case Act::TargetLock: return "l";
  case Act::BarrelRoll: return "r";
  case Act::Boost:      return "b";
  case Act::Evade:      return "e";
  case Act::Cloak:      return "k";
  case Act::SLAM:       return "s";
  case Act::RotateArc:  return "R";
  case Act::Coordinate: return "R";
  default:              return "o";
  }
}

void ForEachAction(Act actions, std::function<void(Act)>f) {
  for(int i=0; i<sizeof(Act)*8; i++) {
    uint32_t v = (1<<i) & (uint32_t)actions;
    if(v) {
      Act a = (Act)v;
      f(a);
    }
  }
}


// Upgrades
std::string UpgToString(Upg u) {
  switch(u) {
  case Upg::Modification:      return "mod";
  case Upg::Elite:             return "ept";
  case Upg::Torpedo:           return "torpedo";
  case Upg::Astromech:         return "amd";
  case Upg::Turret:            return "turret";
  case Upg::Missile:           return "missile";
  case Upg::Title:             return "title";
  case Upg::Crew:              return "crew";
  case Upg::Cannon:            return "cannon";
  case Upg::Bomb:              return "bomb";
  case Upg::System:            return "system";
  case Upg::SalvagedAstromech: return "samd";
  case Upg::Illicit:           return "illicit";
  case Upg::Tech:              return "tech";
  default:                     return "???";
  }
}

std::string GetUpgGlyph(Upg u) {
  switch(u) {
  case Upg::Modification:      return "m";
  case Upg::Elite:             return "E";
  case Upg::Torpedo:           return "P";
  case Upg::Astromech:         return "A";
  case Upg::Turret:            return "U";
  case Upg::Missile:           return "M";
  case Upg::Title:             return "t";
  case Upg::Crew:              return "W";
  case Upg::Cannon:            return "C";
  case Upg::Bomb:              return "B";
  case Upg::System:            return "S";
  case Upg::SalvagedAstromech: return "V";
  case Upg::Illicit:           return "I";
  case Upg::Tech:              return "X";
  default:                     return "";
  }
}
