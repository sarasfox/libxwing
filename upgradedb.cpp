#include "upgrade.h"
#include "shared.h"
#include "pilot.h"
#include <list>


static SModifier SNone = [](const Pilot&) { return 0;};
static AModifier ANone = [](const Pilot&) { return Act::None;};
static UModifier UNone = [](const Pilot&) { return std::vector<Upg>();};

#define S(x)  [](Pilot p) { return x;}

#define cTIX1 [](Pilot p) {for(Upgrade u : p.GetAppliedUpgrades()){ if(u.GetType()==Upg::System){ if(u.GetCost()<=4){return 0-u.GetCost();}else{return -4;} }} return 0;}

#define aBOSL [](Pilot p) { return Act::SLAM;}
#define aENUP [](Pilot p) { return Act::Boost;}
#define aMFAL [](Pilot p) { return Act::Evade;}
#define aMHUN [](Pilot p) { return Act::BarrelRoll;}
#define aTCOM [](Pilot p) { return Act::TargetLock;}
#define aVECT [](Pilot p) { return Act::BarrelRoll;}

#define uANDR [](Pilot p) { return std::vector<Upg>{Upg::Bomb, Upg::Bomb};}
#define uAWTP [](Pilot p) { return std::vector<Upg>{Upg::Elite};}
#define uBWE2 [](Pilot p) { return std::vector<Upg>{Upg::Crew};}
#define uR2D6 [](Pilot p) { return std::vector<Upg>{Upg::Elite};}
#define uRGTI [](Pilot p) { return std::vector<Upg>{Upg::Modification};}
#define uSABW [](Pilot p) { return std::vector<Upg>{Upg::Bomb};}
#define uaTIS [](Pilot p) { return std::vector<Upg>{Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb};}
#define urTIS [](Pilot p) { return std::vector<Upg>{Upg::Crew, Upg::Crew};}
#define uSCOM [](Pilot p) { return std::vector<Upg>{Upg::Illicit, Upg::Modification};}
#define uTIX1 [](Pilot p) { return std::vector<Upg>{Upg::System};}
#define uTIX7 [](Pilot p) { return std::vector<Upg>{Upg::Cannon,Upg::Missile};}
#define uVIRA [](Pilot p) { return std::vector<Upg>{Upg::System,Upg::Illicit};}
#define uSAMP [](Pilot p) { return std::vector<Upg>{Upg::Crew,Upg::Illicit};}

static RestrictionCheck RNone = [](Pilot p) { return true;};
static RestrictionCheck RC(Faction f, BaseSize b, RestrictionCheck other) {
  return [f, b, other](Pilot p) {
    bool ret = true;
    if(f != p.GetFaction()) {
      printf("RESTRICTION ERROR - Faction: Requires %s but played on %s\n", FactionToString(f).c_str(), FactionToString(p.GetFaction()).c_str());
      ret = false;
    }
    if(b != p.GetBaseSize()) {
      printf("RESTRICTION ERROR - Base: Requires %s but played on %s\n", BaseSizeToString(b).c_str(), BaseSizeToString(b).c_str());
      ret = false;
    }
    if(!other(p)) {
      ret = false;
    }
    return true;
  };
}

static RestrictionCheck Ship(std::string sh) {
  return [sh](Pilot p) {
    if(p.GetShipNameXws() == sh) {
      return true;
    } else {
      printf("RESTRICTION ERROR - Ship: Requires %s but played on %s\n", sh.c_str(), p.GetShipNameXws().c_str());
      return false;
    }
  };
}

static RestrictionCheck TIE() {
  return [](Pilot p) {
    if(p.GetShipNameXws().find("tie") != std::string::npos) {
      return true;
    } else {
      printf("RESTRICTION ERROR - Ship: Requires TIE but played on %s\n", p.GetShipNameXws().c_str());
      return false;
    }
  };
}

static RestrictionCheck XW() {
  return [](Pilot p) {
    if(p.GetShipNameXws().find("xwing") != std::string::npos) {
      return true;
    } else {
      printf("RESTRICTION ERROR - Ship: Requires X-Wing but played on %s\n", p.GetShipNameXws().c_str());
      return false;
    }
  };
}

static RestrictionCheck YT() {
  return [](Pilot p) {
    if((p.GetShipNameXws() == "yt1300") || (p.GetShipNameXws() == "yt2400")) {
      return true;
    } else {
      printf("RESTRICTION ERROR - Ship: Requires YT-1300 or YT-2400 but played on %s\n", p.GetShipNameXws().c_str());
      return false;
    }
  };
}

static RestrictionCheck AT() {
  return [](Pilot p) {
    if((p.GetModActions() & Act::Boost) == Act::Boost) {
      return true;
    } else {
      printf("RESTRICTION ERROR - Action: Autothrusters requires Boost\n");
      return false;
    }
  };
}



std::list<Upgrade> Upgrade::upgrades = {
  // Name                            ShortName           XwsName                      Type                    Slots                    Co  uni    lim      sk     at     ag     hu     sh     co     +act   -act   +upg   -upg
  { "Determination",                "Determination",    "determination",              Upg::Elite,             {Upg::Elite},             1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Marksmanship",                 "Marksmanship",     "marksmanship",               Upg::Elite,             {Upg::Elite},             3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Expert Handling",              "Expert Hand",      "experthandling",             Upg::Elite,             {Upg::Elite},             2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "SwarmTactics",                 "Sewarm Tact",      "swarmtactics",               Upg::Elite,             {Upg::Elite},             2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Squad Leader",                 "Squad Leader",     "squadleader",                Upg::Elite,             {Upg::Elite},             2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Draw Their Fire",              "Draw Their Fire",  "drawtheirfire",              Upg::Elite,             {Upg::Elite},             1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Elusiveness",                  "Elusiveness",      "elusiveness",                Upg::Elite,             {Upg::Elite},             2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Veteran Instincts",            "VI",               "veteraninstincts",           Upg::Elite,             {Upg::Elite},             1, false, false, {  S(2), SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Expose",                       "Expose",           "expose",                     Upg::Elite,             {Upg::Elite},             4, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Deadeye",                      "Deadeye",          "deadeye",                    Upg::Elite,             {Upg::Elite},             1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::Small, RNone) },
  { "Push the Limit",               "PTL",              "pushthelimit",               Upg::Elite,             {Upg::Elite},             3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Daredevil",                    "Daredevil",        "daredevil",                  Upg::Elite,             {Upg::Elite},             3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Adrenaline Rush",              "Adrenaline Rsh",   "adrenalinerush",             Upg::Elite,             {Upg::Elite},             1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Opportunist",                  "Opporunist",       "opportunist",                Upg::Elite,             {Upg::Elite},             4, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Decoy",                        "Decoy",            "decoy",                      Upg::Elite,             {Upg::Elite},             2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Wingman",                      "Wingman",          "wingman",                    Upg::Elite,             {Upg::Elite},             2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Outmaneuver",                  "Outmaneuver",      "outmaneuver",                Upg::Elite,             {Upg::Elite},             3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Predator",                     "Predator",         "predator",                   Upg::Elite,             {Upg::Elite},             3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Lone Wolf",                    "Lone Wolf",        "lonewolf",                   Upg::Elite,             {Upg::Elite},             2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Stay on Target",               "Stay on Trgt",     "stayontarget",               Upg::Elite,             {Upg::Elite},             2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Intimidation",                 "Intimidation",     "intimidation",               Upg::Elite,             {Upg::Elite},             2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Ruthlessness",                 "Ruthlessness",     "ruthlessness",               Upg::Elite,             {Upg::Elite},             3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Empire, BaseSize::All,   RNone) },
  { "Bodyguard",                    "Bodyguard",        "bodyguard",                  Upg::Elite,             {Upg::Elite},             2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Scum,   BaseSize::All,   RNone) },
  { "Calculation",                  "Calculation",      "calculation",                Upg::Elite,             {Upg::Elite},             1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Crack Shot",                   "Crack Shot",       "crackshot",                  Upg::Elite,             {Upg::Elite},             1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Lightning Reflexes",           "Lightning Rf",     "lightningreflexes",          Upg::Elite,             {Upg::Elite},             1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::Small, RNone) },
  { "Wired",                        "Wired",            "wired",                      Upg::Elite,             {Upg::Elite},             1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Cool Hand",                    "Cool Hand",        "coolhand",                   Upg::Elite,             {Upg::Elite},             1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Juke",                         "Juke",             "juke",                       Upg::Elite,             {Upg::Elite},             2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::Small, RNone) },
  { "Adaptability",                 "Adaptability",     "adaptability",               Upg::Elite,             {Upg::Elite},             0, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Rage",                         "Rage",             "rage",                       Upg::Elite,             {Upg::Elite},             1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Attanni Mindlink",             "Attani Mindlink",  "attannimindlink",            Upg::Elite,             {Upg::Elite},             1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Scum,   BaseSize::All,   RNone) },
  { "Fearlessness",                 "Fearlessness",     "fearlessness",               Upg::Elite,             {Upg::Elite},             1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Scum,   BaseSize::All,   RNone) },
  { "Snap Shot",                    "Snap Shot",        "snapshot",                   Upg::Elite,             {Upg::Elite},             2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Trick Shot",                   "Trick Shot",       "trickshot",                  Upg::Elite,             {Upg::Elite},             0, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Expertise",                    "Expertise",        "expertise",                  Upg::Elite,             {Upg::Elite},             4, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Swarm Leader",                 "Swarm Leader",     "swarmleader",                Upg::Elite,             {Upg::Elite},             3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "A Score to Settle",            "Score to Settle",  "ascoretosettle",             Upg::Elite,             {Upg::Elite},             0, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },

  { "R2-D2",                        "R2-D2",            "r2d2",                       Upg::Astromech,         {Upg::Astromech},         4, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "R2-F2",                        "R2-F2",            "r2f2",                       Upg::Astromech,         {Upg::Astromech},         4, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "R5 Astromech",                 "R5",               "r5astromech",                Upg::Astromech,         {Upg::Astromech},         1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "R5-K6",                        "R5-K6",            "r5k6",                       Upg::Astromech,         {Upg::Astromech},         1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "R2 Astromech",                 "R2",               "r2astromech",                Upg::Astromech,         {Upg::Astromech},         1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "R5-D8",                        "R5-D8",            "r5d8",                       Upg::Astromech,         {Upg::Astromech},         3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "R2-D6",                        "R2-D6",            "r2d6",                       Upg::Astromech,         {Upg::Astromech},         1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, uR2D6, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "R3-A2",                        "R3-A4",            "r3a2",                       Upg::Astromech,         {Upg::Astromech},         2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "R4-D6",                        "R4-D6",            "r4d6",                       Upg::Astromech,         {Upg::Astromech},         1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "R5-P9",                        "R5-P9",            "r5p9",                       Upg::Astromech,         {Upg::Astromech},         3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "R7 Astromech",                 "R7",               "r7astromech",                Upg::Astromech,         {Upg::Astromech},         2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "R7-T1",                        "R7-T1",            "r7t1",                       Upg::Astromech,         {Upg::Astromech},         3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "BB-8",                         "BB-8",             "bb8",                        Upg::Astromech,         {Upg::Astromech},         2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "R5-X3",                        "R5-X3",            "r5x3",                       Upg::Astromech,         {Upg::Astromech},         1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Targeting Astromech",          "Targeting Ast",    "targetingastromech",         Upg::Astromech,         {Upg::Astromech},         2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "R3 Astromech",                 "R3",               "r3astromech",                Upg::Astromech,         {Upg::Astromech},         2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "M9-G8",                        "M9-G8",            "m9g8",                       Upg::Astromech,         {Upg::Astromech},         3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  
  { "Proton Torpedoes",             "Proton Torp",      "protontorpedoes",            Upg::Torpedo,           {Upg::Torpedo},           4, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Adv. Proton Torpedoes",        "Adv. Proton",      "advprotontorpedoes",         Upg::Torpedo,           {Upg::Torpedo},           6, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Flechette Torpedoes",          "Flechette",        "flechettetorpedoes",         Upg::Torpedo,           {Upg::Torpedo},           2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Ion Torpedoes",                "Ion",              "iontorpedoes",               Upg::Torpedo,           {Upg::Torpedo},           5, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Bomb Loadout",                 "Bomb Loadout",     "bombloadout",                Upg::Torpedo,           {Upg::Torpedo},           0, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("ywing")) },
  { "Extra Munitions",              "Extra Mun",        "extramunitions",             Upg::Torpedo,           {Upg::Torpedo},           2, false, true,  { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Plasma Torpedoes",             "Plasma",           "plasmatorpedoes",            Upg::Torpedo,           {Upg::Torpedo},           3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Seismic Torpedo",              "Seismic",          "seismictorpedo",             Upg::Torpedo,           {Upg::Torpedo},           2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },

  { "Ion Cannon Turret",            "Ion Can Tur",      "ioncannonturret",            Upg::Turret,            {Upg::Turret},            5, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Blaster Turret",               "Blaster Turret",   "blasterturret",              Upg::Turret,            {Upg::Turret},            4, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Autoblaster Turret",           "Autoblaster",      "autoblasterturret",          Upg::Turret,            {Upg::Turret},            2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Twin Laser Turret",            "TLT",              "twinlaserturret",            Upg::Turret,            {Upg::Turret},            6, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Dorsal Turret",                "Dorsal Turret",    "dorsalturret",               Upg::Turret,            {Upg::Turret},            3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },

  { "Cluster Missiles",             "Cluster Msls",     "clustermissiles",            Upg::Missile,           {Upg::Missile},           4, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Concussion Missiles",          "Concussion Msls",  "concussionmissiles",         Upg::Missile,           {Upg::Missile},           4, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Assault Missiles",             "Assault Msls",     "assaultmissiles",            Upg::Missile,           {Upg::Missile},           5, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Homing Missiles",              "Homing",           "homingmissiles",             Upg::Missile,           {Upg::Missile},           5, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Ion Pulse Missile",            "Ion Pulse",        "ionpulsemissile",            Upg::Missile,           {Upg::Missile},           3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Chardaan Refit",               "Chardaan Rft",     "chardaanrefit",              Upg::Missile,           {Upg::Missile},          -2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("awing")) },
  { "Proton Rockets",               "Proton Rockets",   "protonrockets",              Upg::Missile,           {Upg::Missile},           3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Adv Homing Missile",           "Adv Homing",       "advhomingmissiles",          Upg::Missile,           {Upg::Missile},           3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "XX-23 S-Thread Tracers",       "XX23 Tracers",     "xx23sthreadtracers",         Upg::Missile,           {Upg::Missile},           1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },

  { "Chewbacca",                    "Chewbacca",        "chewbacca",                  Upg::Crew,              {Upg::Crew},              4, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Luke Skywalker",               "Luke Skywalker",   "lukeskywalker",              Upg::Crew,              {Upg::Crew},              7, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Nien Nunb",                    "Nien Nunb",        "niennunb",                   Upg::Crew,              {Upg::Crew},              1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Weapons Engineer",             "Weapons Eng",      "weaponsengineer",            Upg::Crew,              {Upg::Crew},              3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Gunner",                       "Gunner",           "gunner",                     Upg::Crew,              {Upg::Crew},              5, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Mercenary Copilot",            "Merc Copilot",     "mercenarycopilot",           Upg::Crew,              {Upg::Crew},              2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Intelligence Agent",           "Intel Agent",      "intelligenceagent",          Upg::Crew,              {Upg::Crew},              1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Recon Specialist",             "Recon Spec",       "reconspecialist",            Upg::Crew,              {Upg::Crew},              3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Saboteur",                     "Saboteur",         "saboteur",                   Upg::Crew,              {Upg::Crew},              2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Darth Vader",                  "Vader",            "darthvader",                 Upg::Crew,              {Upg::Crew},              3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Empire, BaseSize::All,   RNone) },
  { "Flight Instructor",            "Flight Inst",      "flightinstructor",           Upg::Crew,              {Upg::Crew},              4, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Navigator",                    "Navigator",        "navigator",                  Upg::Crew,              {Upg::Crew},              3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Rebel Captive",                "Rebel Captive",    "rebelcaptive",               Upg::Crew,              {Upg::Crew},              3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Empire, BaseSize::All,   RNone) },
  { "C-3PO",                        "C-3PO",            "c3po",                       Upg::Crew,              {Upg::Crew},              3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Han Solo",                     "Han Solo",         "hansolo",                    Upg::Crew,              {Upg::Crew},              2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Leia Organa",                  "Leia Organa",      "leiaorgana",                 Upg::Crew,              {Upg::Crew},              4, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "R2-D2",                        "R2-D2",            "r2d2",                       Upg::Crew,              {Upg::Crew},              4, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Tactician",                    "Tactician",        "tactician",                  Upg::Crew,              {Upg::Crew},              2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Jan Ors",                      "Jan Ors",          "janors",                     Upg::Crew,              {Upg::Crew},              2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Kyle Katarn",                  "Kyle Katarn",      "kylekatarn",                 Upg::Crew,              {Upg::Crew},              3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "\"Leebo\"",                    "Leebo",            "leebo",                      Upg::Crew,              {Upg::Crew},              2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Dash Rendar",                  "Dash",             "dashrendar",                 Upg::Crew,              {Upg::Crew},              2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Lando Calrissian",             "Lando",            "landocalrissian",            Upg::Crew,              {Upg::Crew},              3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Fleet Officer",                "Fleet Officer",    "fleetofficer",               Upg::Crew,              {Upg::Crew},              3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Empire, BaseSize::All,   RNone) },
  { "Mara Jade",                    "Mara Jade",        "marajade",                   Upg::Crew,              {Upg::Crew},              3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Empire, BaseSize::All,   RNone) },
  { "Moff Jerjerrod",               "Moff Jerjerrod",   "moffjerjerrod",              Upg::Crew,              {Upg::Crew},              2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Empire, BaseSize::All,   RNone) },
  { "Ysanne Isard",                 "Ysanne Isard",     "ysanneisard",                Upg::Crew,              {Upg::Crew},              4, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Empire, BaseSize::All,   RNone) },
  { "Greedo",                       "Greedo",           "greedo",                     Upg::Crew,              {Upg::Crew},              1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Scum,   BaseSize::All,   RNone) },
  { "K4 Security Droid",            "K4",               "k4securitydroid",            Upg::Crew,              {Upg::Crew},              3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Scum,   BaseSize::All,   RNone) },
  { "Outlaw Tech",                  "Outlaw Tech",      "outlawtech",                 Upg::Crew,              {Upg::Crew},              2, false, true,  { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Scum,   BaseSize::All,   RNone) },
  { "Emperor Palpatine",            "Palp",             "emperorpalpatine",           Upg::Crew,              {Upg::Crew,Upg::Crew},    8, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Empire, BaseSize::All,   RNone) },
  { "Bossk",                        "Bossk",            "bossk",                      Upg::Crew,              {Upg::Crew},              2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Scum,   BaseSize::All,   RNone) },
  { "Bombardier",                   "Bombardier",       "bombardier",                 Upg::Crew,              {Upg::Crew},              1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Agent Kallus",                 "Agent Kallus",     "agentkallus",                Upg::Crew,              {Upg::Crew},              2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Empire, BaseSize::All,   RNone) },
  { "Rear Admiral Chiraneau",       "RADM Chiraneau",   "rearadmiralchiraneau",       Upg::Crew,              {Upg::Crew},              3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Empire, BaseSize::All,   RNone) },
  //{ "Construction Droid",           "Const Droid",      "constructiondroid",          Upg::Crew,              {Upg::Crew},              3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All, BaseSize::All, RNone) },
  { "\"Chopper\"",                  "Chopper",          "chopper",                    Upg::Crew,              {Upg::Crew},              0, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "\"Zeb\" Orrelios",             "Zeb",              "zeborrelios",                Upg::Crew,              {Upg::Crew},              1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Ezra Bridger",                 "Ezra",             "ezrabridger",                Upg::Crew,              {Upg::Crew},              3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Hera Syndulla",                "Hera",             "herasyndulla",               Upg::Crew,              {Upg::Crew},              1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Kanan Jarrus",                 "Kanan",            "kananjarrus",                Upg::Crew,              {Upg::Crew},              3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Sabine Wren",                  "Sabine",           "sabinewren",                 Upg::Crew,              {Upg::Crew},              2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, uSABW, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "4-LOM",                        "4-LOM",            "4lom",                       Upg::Crew,              {Upg::Crew},              1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Scum,   BaseSize::All,   RNone) },
  { "Zuckuss",                      "Zuckuss",          "zuckuss",                    Upg::Crew,              {Upg::Crew},              1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Scum,   BaseSize::All,   RNone) },
  { "Gonk",                         "Gonk",             "gonk",                       Upg::Crew,              {Upg::Crew},              2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Scum,   BaseSize::All,   RNone) },
  { "Boba Fett",                    "Boba Fett",        "bobafett",                   Upg::Crew,              {Upg::Crew},              1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Scum,   BaseSize::All,   RNone) },
  { "Dengar",                       "Dengar",           "dengar",                     Upg::Crew,              {Upg::Crew},              3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Scum,   BaseSize::All,   RNone) },
  { "Systems Officer",              "Sys Officer",      "systemsofficer",             Upg::Crew,              {Upg::Crew},              2, false, true, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Empire,  BaseSize::All,   RNone) },
  { "Tail Gunner",                  "Tail Gunner",      "tailgunner",                 Upg::Crew,              {Upg::Crew},              2, false, true,  { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Latts Razzi",                  "Latts Razzi",      "lattsrazzi",                 Upg::Crew,              {Upg::Crew},              2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Scum,   BaseSize::All,   RNone) },
  { "Ketsu Onyo",                   "Ketsu Onyo",       "ketsuonyo",                  Upg::Crew,              {Upg::Crew},              1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Scum,   BaseSize::All,   RNone) },
  { "IG-88D",                       "IG-88D",           "ig88d",                      Upg::Crew,              {Upg::Crew},              1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Scum,   BaseSize::All,   RNone) },
  { "Finn",                         "Finn",             "finn",                       Upg::Crew,              {Upg::Crew},              5, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Rey",                          "Rey",              "rey",                        Upg::Crew,              {Upg::Crew},              2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Hotshot Copilot",              "Hotshot Copilot",  "hotshotcopilot",             Upg::Crew,              {Upg::Crew},              4, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Jyn Erso",                     "Jyn Erso",         "jynerso",                    Upg::Crew,              {Upg::Crew},              2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Cassian Andor",                "Cassian Andor",    "cassianandor",               Upg::Crew,              {Upg::Crew},              2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Baze Malbus",                  "Baze Malbus",      "bazemalbus",                 Upg::Crew,              {Upg::Crew},              3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Bistan",                       "Bistan",           "bistan",                     Upg::Crew,              {Upg::Crew},              2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Bodhi Rook",                   "Bodhi Rook",       "bodhirook",                  Upg::Crew,              {Upg::Crew},              1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Inspiring Recruit",            "Insp Recruit",     "inspiringrecruit",           Upg::Crew,              {Upg::Crew},              1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Captain Rex",                  "Capt. Rex",        "captainrex",                 Upg::Crew,              {Upg::Crew},              2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   RNone) },
  { "Kylo Ren",                     "Kylo Ren",         "kyloren",                    Upg::Crew,              {Upg::Crew},              3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Empire, BaseSize::All,   RNone) },
  { "General Hux",                  "Gen. Hux",         "generalhux",                 Upg::Crew,              {Upg::Crew},              5, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Empire, BaseSize::All,   RNone) },
  { "Operations Specialist",        "Ops Specialist",   "operationsspecialist",       Upg::Crew,              {Upg::Crew},              3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Empire, BaseSize::All,   RNone) },
  { "Unkar Plutt",                  "Unkay Plutt",      "unkarplutt",                 Upg::Crew,              {Upg::Crew},              1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Scum,   BaseSize::All,   RNone) },
  { "BoShek",                       "BoShek",           "boshek",                     Upg::Crew,              {Upg::Crew},             99, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Scum,   BaseSize::All,   RNone) },

  { "Millennium Falcon",            "MF",               "millenniumfalcon",           Upg::Title,             {Upg::Title},             1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, aMFAL, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("yt1300")) },
  { "Slave 1",                      "Slave 1",          "slave1",                     Upg::Title,             {Upg::Title},             0, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("firespray31")) },
  { "Moldy Crow",                   "Moldy Crow",       "moldycrow",                  Upg::Title,             {Upg::Title},             3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("hwk290")) },
  { "ST-321",                       "ST-321",           "st321",                      Upg::Title,             {Upg::Title},             3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("lambdaclassshuttle")) },
  { "Royal Guard TIE",              "Royal Guard",      "royalguardtie",              Upg::Title,             {Upg::Title},             0, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, uRGTI, UNone }, RC(Faction::All,    BaseSize::All,   Ship("tieinterceptor")) },
  { "A-Wing Test Pilot",            "Test Pilot",       "awingtestpilot",             Upg::Title,             {Upg::Title},             0, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, uAWTP, UNone }, RC(Faction::All,    BaseSize::All,   Ship("awing")) },
  { "Outrider",                     "Outrider",         "outrider",                   Upg::Title,             {Upg::Title},             5, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("yt2400")) },
  { "Dauntless",                    "Dauntless",        "dauntless",                  Upg::Title,             {Upg::Title},             2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("vt49")) },
  { "BTL-A4 Y-Wing",                "BTL-A4",           "btla4ywing",                 Upg::Title,             {Upg::Title},             0, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("ywing")) },
  { "Andrasta",                     "Andrasta",         "andrasta",                   Upg::Title,             {Upg::Title},             0, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, uANDR, UNone }, RC(Faction::All,    BaseSize::All,   Ship("firespray31")) },
  { "\"Heavy Scyk\" Interceptor",   "Heavy Scyk",       "heavyscykinterceptor",       Upg::Title,             {Upg::Title},             2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("m3a")) }, // <-- crazy action modifier
  { "Virago",                       "Virago",           "virago",                     Upg::Title,             {Upg::Title},             1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, uVIRA, UNone }, RC(Faction::All,    BaseSize::All,   Ship("starviper")) },
  { "IG-2000",                      "IG-2000",          "ig2000",                     Upg::Title,             {Upg::Title},             0, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("aggressor")) },
  { "TIE/x1",                       "TIE/x1",           "tiex1",                      Upg::Title,             {Upg::Title},             0, false, false, { SNone, SNone, SNone, SNone, SNone, cTIX1, ANone, ANone, uTIX1, UNone }, RC(Faction::All,    BaseSize::All,   Ship("tieadvanced")) },
  { "Hound's Tooth",                "Hounds Tooth",     "houndstooth",                Upg::Title,             {Upg::Title},             6, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("yv666")) },
  { "Ghost",                        "Ghost",            "ghost",                      Upg::Title,             {Upg::Title},             0, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("vcx100")) },
  { "Phantom",                      "Phantom",          "phantom",                    Upg::Title,             {Upg::Title},             0, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "TIE/v1",                       "TIE/v1",           "tiev1",                      Upg::Title,             {Upg::Title},             1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("tieadvprototype")) },
  { "Mist Hunter",                  "Mist Hunter",      "misthunter",                 Upg::Title,             {Upg::Title},             0, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, aMHUN, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("g1astarfighter")) },
  { "Punishing One",                "Punishing One",    "punishingone",               Upg::Title,             {Upg::Title},            12, true,  false, { SNone,  S(1), SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("jumpmaster5000")) },
  { "TIE/x7",                       "TIE/x7",           "tiex7",                      Upg::Title,             {Upg::Title},            -2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, uTIX7 }, RC(Faction::All,    BaseSize::All,   Ship("tiedefender")) },
  { "TIE/D",                        "TIE/D",            "tied",                       Upg::Title,             {Upg::Title},             0, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("tiedefender")) },
  { "TIE Shuttle",                  "TIE Shuttle",      "tieshuttle",                 Upg::Title,             {Upg::Title},             0, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, uaTIS, urTIS }, RC(Faction::All,    BaseSize::All,   Ship("tiebomber")) },
  { "Alliance Overhaul",            "Alli Overhaul",    "allianceoverhaul",           Upg::Title,             {Upg::Title},             0, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("arc170")) },
  { "Special Ops Training",         "SpecOps Train",    "specialopstraining",         Upg::Title,             {Upg::Title},             0, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("tiesf")) },
  { "Concord Dawn Protector",       "CD Protector",     "concorddawnprotector",       Upg::Title,             {Upg::Title},             1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("protectoratestarfighter")) },
  { "Shadow Caster",                "Shadow Caster",    "shadowcaster",               Upg::Title,             {Upg::Title},             3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("lancerclasspursuitcraft")) },
  { "Black One",                    "Black One",        "blackone",                   Upg::Title,             {Upg::Title},             1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("t70xwing")) },
  { "Millennium Falcon",            "MF (HOTR)",        "millenniumfalcon-swx57",     Upg::Title,             {Upg::Title},             1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("yt1300")) },
  { "Pivot Wing",                   "Pivot Wing",       "pivotwing",                  Upg::Title,             {Upg::Title},             0, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("uwing")) },
  { "Adaptive Ailerons",            "Adapt Ailerons",   "adaptiveailerons",           Upg::Title,             {Upg::Title},             0, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("tiestriker")) },
  { "Sabine's Masterpiece",         "Sabine's Mpiece",  "sabinesmasterpiece",         Upg::Title,             {Upg::Title},             1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, uSAMP, UNone }, RC(Faction::Rebel,  BaseSize::All,   Ship("tiefighter")) },
  { "Kylo Ren's Shuttle",           "Kylo Ren's",       "kylorensshuttle",            Upg::Title,             {Upg::Title},             2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, uSAMP, UNone }, RC(Faction::All,    BaseSize::All,   Ship("upsilonclassshuttle")) },

  { "Engine Upgrade",               "EU",               "engineupgrade",              Upg::Modification,      {Upg::Modification},      4, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, aENUP, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Shield Upgrade",               "SU",               "shieldupgrade",              Upg::Modification,      {Upg::Modification},      4, false, false, { SNone, SNone, SNone, SNone,  S(1), SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Stealth Device",               "Stealth Dev",      "stealthdevice",              Upg::Modification,      {Upg::Modification},      3, false, false, { SNone, SNone,  S(1), SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Anti-Pursuit Lasers",          "AntiPursuit L",    "antipursuitlasers",          Upg::Modification,      {Upg::Modification},      2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::Large, RNone) },
  { "Hull Upgrade",                 "HU",               "hullupgrade",                Upg::Modification,      {Upg::Modification},      3, false, false, { SNone, SNone, SNone,  S(1), SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Targeting Computer",           "Targeting Comp",   "targetingcomputer",          Upg::Modification,      {Upg::Modification},      2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, aTCOM, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "B-Wing/E2",                    "E2",               "bwinge2",                    Upg::Modification,      {Upg::Modification},      1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, uBWE2, UNone }, RC(Faction::All,    BaseSize::All,   Ship("bwing")) },
  { "Munitions Failsafe",           "Muni Failsafe",    "munitionsfailsafe",          Upg::Modification,      {Upg::Modification},      1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Advanced Cloaking Device",     "Adv Cloak Dev",    "advancedcloakingdevice",     Upg::Modification,      {Upg::Modification},      4, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("tiephantom")) },
  { "Stygium Particle Accelerator", "Styg Part Accl",   "stygiumparticleaccelerator", Upg::Modification,      {Upg::Modification},      2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Countermeasures",              "Countermeas",      "countermeasures",            Upg::Modification,      {Upg::Modification},      3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::Large, RNone) },
  { "Experimental Interface",       "EI",               "experimentalinterface",      Upg::Modification,      {Upg::Modification},      3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Tactical Jammer",              "Tact Jammer",      "tacticaljammer",             Upg::Modification,      {Upg::Modification},      1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::Large, RNone) },
  { "Autothrusters",                "Autothrusters",    "autothrusters",              Upg::Modification,      {Upg::Modification},      2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   AT()) },
  { "Ion Projector",                "Ion Projector",    "ionprojector",               Upg::Modification,      {Upg::Modification},      2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::Large, RNone) },
  { "Maneuvering Fins",             "Maneuv Fins",      "maneuveringfins",            Upg::Modification,      {Upg::Modification},      1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("yv666")) },
  { "Advanced SLAM",                "Adv SLAM",         "advancedslam",               Upg::Modification,      {Upg::Modification},      2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Twin Ion Engine Mk. 2",        "TIE Mk 2",         "twinionenginemk2",           Upg::Modification,      {Upg::Modification},      1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   TIE()) },
  { "Integrated Astromech",         "Integrated Ast",   "integratedastromech",        Upg::Modification,      {Upg::Modification},      0, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   XW()) },
  { "Guidance Chips",               "Guidance Chips",   "guidancechips",              Upg::Modification,      {Upg::Modification},      0, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Long-Range Scanners",          "LR Scanners",      "longrangescanners",          Upg::Modification,      {Upg::Modification},      0, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Vectored Thrusters",           "Vectored Thr",     "vectoredthrusters",          Upg::Modification,      {Upg::Modification},      2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, aVECT, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::Small, RNone) },
  { "Gyroscopic Targeting",         "Gyro Targeting",   "gyroscopictargeting",        Upg::Modification,      {Upg::Modification},      2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("lanerclasspursuitcraft")) },
  { "Smuggling Compartment",        "Smuggling Comp",   "smugglingcompartment",       Upg::Modification,      {Upg::Modification},      0, false, true,  { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, uSCOM, UNone }, RC(Faction::All,    BaseSize::All,   YT()) },
  { "Lightweight Frame",            "LW Frame",         "lightweightframe",           Upg::Modification,      {Upg::Modification},      2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   TIE()) },
  { "Captured TIE",                 "Captured TIE",     "capturedtie",                Upg::Modification,      {Upg::Modification},      1, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::Rebel,  BaseSize::All,   Ship("tiefighter")) },
  { "Spacetug Tractor Array",       "Spacetug Tractor", "spacetugtractorarray",       Upg::Modification,      {Upg::Modification},      2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("quadjumper")) },

  { "Heavy Laser Cannon",           "HLC",              "heavylasercannon",           Upg::Cannon,            {Upg::Cannon},            7, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Ion Cannon",                   "Ion Cannon",       "ioncannon",                  Upg::Cannon,            {Upg::Cannon},            3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Autoblaster",                  "Autobaster",       "autoblaster",                Upg::Cannon,            {Upg::Cannon},            5, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "\"Mangler\" Cannon",           "Mangler",          "manglercannon",              Upg::Cannon,            {Upg::Cannon},            4, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Flechette Cannon",             "Flechette",        "flechettecannon",            Upg::Cannon,            {Upg::Cannon},            2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Tractor Beam",                 "Tractor Beam",     "tractorbeam",                Upg::Cannon,            {Upg::Cannon},            1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },

  { "Proximity Mines",              "Prox Mines",       "proximitymines",             Upg::Bomb,              {Upg::Bomb},              3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Seismic Charges",              "Seismic Chrgs",    "seismiccharges",             Upg::Bomb,              {Upg::Bomb},              2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Proton Bombs",                 "Proton Bombs",     "protonbombs",                Upg::Bomb,              {Upg::Bomb},              5, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Conner Net",                   "Connor Net",       "connernet",                  Upg::Bomb,              {Upg::Bomb},              4, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Ion Bombs",                    "Ion Bombs",        "ionbombs",                   Upg::Bomb,              {Upg::Bomb},              2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Cluster Mines",                "Cluster Mines",    "clustermines",               Upg::Bomb,              {Upg::Bomb},              4, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Thermal Detonators",           "Therm Det",        "thermaldetonators",          Upg::Bomb,              {Upg::Bomb},              3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },

  { "Advanced Sensors",             "Adv Sensors",      "advancedsensors",            Upg::System,            {Upg::System},            3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Sensor Jammer",                "Sensor Jammer",    "sensorjammer",               Upg::System,            {Upg::System},            4, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Fire-Control System",          "FCS",              "firecontrolsystem",          Upg::System,            {Upg::System},            2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Enhanced Scopes",              "Enh Scopes",       "enhancedscopes",             Upg::System,            {Upg::System},            1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Accuracy Corrector",           "Acc Correct",      "accuracycorrector",          Upg::System,            {Upg::System},            3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Adv. Targeting Computer",      "ATC",              "advtargetingcomputer",       Upg::System,            {Upg::System},            5, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   Ship("tieadvanced")) },
  { "Reinforced Deflectors",        "Reinforced Def",   "reinforceddeflectors",       Upg::System,            {Upg::System},            3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::Large, RNone) },
  { "Electronic Baffle",            "Electronic Baf",   "electronicbaffle",           Upg::System,            {Upg::System},            1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Collision Detector",           "Collision Det",    "collisiondetector",          Upg::System,            {Upg::System},            0, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },

  { "\"Genius\"",                   "Genius",           "genius",                     Upg::SalvagedAstromech, {Upg::SalvagedAstromech}, 0, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "R4 Agromech",                  "R4",               "r4agromech",                 Upg::SalvagedAstromech, {Upg::SalvagedAstromech}, 2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "R4-B11",                       "R4-B11",           "r4b11",                      Upg::SalvagedAstromech, {Upg::SalvagedAstromech}, 3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Salvaged Astromech",           "Salvaged",         "salvagedastromech",          Upg::SalvagedAstromech, {Upg::SalvagedAstromech}, 2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Unhinged Astromech",           "Unhinged",         "unhingedastromech",          Upg::SalvagedAstromech, {Upg::SalvagedAstromech}, 1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "R5-P8",                        "R5-P8",            "r5p8",                       Upg::SalvagedAstromech, {Upg::SalvagedAstromech}, 3, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Overcocked R4",                "Overclkd R4",      "overclockedr4",              Upg::SalvagedAstromech, {Upg::SalvagedAstromech}, 1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },

  { "\"Hot Shot\" Blaster",         "Hot Shot",         "hotshotblaster",             Upg::Illicit,           {Upg::Illicit},           3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Inertial Dampeners",           "Inertial Damp",    "inertialdampeners",          Upg::Illicit,           {Upg::Illicit},           1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Dead Man's Switch",            "Dead Mans Sw",     "deadmansswitch",             Upg::Illicit,           {Upg::Illicit},           2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Feedback Array",               "Feedback Ar",      "feedbackarray",              Upg::Illicit,           {Upg::Illicit},           2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Glitterstim",                  "Glitterstim",      "glitterstim",                Upg::Illicit,           {Upg::Illicit},           2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Cloaking Device",              "Cloak Dev",        "cloakingdevice",             Upg::Illicit,           {Upg::Illicit},           2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::Small, RNone) },
  { "Rigged Cargo Chute",           "Rigged Cargo",     "riggedcargochute",           Upg::Illicit,           {Upg::Illicit},           1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::Large, RNone) },
  { "Black Market Slicer Tools",    "BMST",             "blackmarketslicertools",     Upg::Illicit,           {Upg::Illicit},           1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Burnout SLAM",                 "Burnout SLAM",     "burnoutslam",                Upg::Illicit,           {Upg::Illicit},           1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, aBOSL, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::Large, RNone) },
  { "EMP Device",                   "EMP Device",       "empdevice",                  Upg::Illicit,           {Upg::Illicit},           2, true,  false, { SNone, SNone, SNone, SNone, SNone, SNone, aBOSL, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Scavenger Crane",              "Scavenger Crane",  "scavengercrane",             Upg::Illicit,           {Upg::Illicit},           2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, aBOSL, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  
  { "Weapons Guidance",             "Weap Guidance",    "weaponsguidance",            Upg::Tech,              {Upg::Tech},              2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Comm Relay",                   "Comm Relay",       "commrelay",                  Upg::Tech,              {Upg::Tech},              3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Sensor Cluster",               "Sensor Cluster",   "sensorcluster",              Upg::Tech,              {Upg::Tech},              2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Pattern Analyzer",             "Pattern Analuzer", "patternanalyzer",            Upg::Tech,              {Upg::Tech},              2, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Primed Thrusters",             "Primed Thristers", "primedthrusters",            Upg::Tech,              {Upg::Tech},              1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::Small, RNone) },
  { "Targeting Synchronizer",       "Targeting Sync",   "targetingsynchronizer",      Upg::Tech,              {Upg::Tech},              3, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },
  { "Hyperwave Comm Scanner",       "HW Comm Scanner",  "hyperwavecommscanner",       Upg::Tech,              {Upg::Tech},              1, false, false, { SNone, SNone, SNone, SNone, SNone, SNone, ANone, ANone, UNone, UNone }, RC(Faction::All,    BaseSize::All,   RNone) },

};
