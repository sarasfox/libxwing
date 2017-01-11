#include "pilot.h"
#include "shared.h"
#include <list>



typedef Maneuvers  M;

const Bearing LT = Bearing::LTurn;
const Bearing LB = Bearing::LBank;
const Bearing ST = Bearing::Straight;
const Bearing RB = Bearing::RBank;
const Bearing RT = Bearing::RTurn;
const Bearing KT = Bearing::KTurn;
const Bearing SY = Bearing::Stationary;

const Difficulty G = Difficulty::Green;
const Difficulty W = Difficulty::White;
const Difficulty R = Difficulty::Red;

M mXWING = {                    {4,ST,W},                     {4,KT,R},
            {3,LT,W}, {3,LB,W}, {3,ST,W}, {3,RB,W}, {3,RT,W},
            {2,LT,W}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,W},
                      {1,LB,G}, {1,ST,G}, {1,RB,G}
};

M mTIEFI = {                    {5,ST,W},
                                {4,ST,W},                     {4,KT,R},
            {3,LT,W}, {3,LB,W}, {3,ST,G}, {3,RB,W}, {3,RT,W}, {3,KT,R},
            {2,LT,W}, {2,LB,G}, {2,ST,G}, {2,RB,G}, {2,RT,W},
            {1,LT,W},                               {1,RT,W}
};

M mYWING = {                    {4,ST,R},                     {4,KT,R},
            {3,LT,R}, {3,LB,W}, {3,ST,W}, {3,RB,W}, {3,RT,R},
            {2,LT,W}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,W},
                      {1,LB,W}, {1,ST,G}, {1,RB,W}
};

M mTIEAD = {                    {5,ST,W},
                                {4,ST,W},                     {4,KT,R},
            {3,LT,W}, {3,LB,W}, {3,ST,G}, {3,RB,W}, {3,RT,W},
            {2,LT,W}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,W},
                      {1,LB,G},           {1,RB,G}
};

M mYT130 = {                    {4,ST,W},                     {4,KT,R},
                      {3,LB,W}, {3,ST,W}, {3,RB,W},           {3,KT,R},
            {2,LT,W}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,W},
            {1,LT,W}, {1,LB,G}, {1,ST,G}, {1,RB,G}, {1,RT,W}
};

M mFSP31 = {                    {4,ST,W},                     {4,KT,R},
            {3,LT,W}, {3,LB,W}, {3,ST,W}, {3,RB,W}, {1,RT,W}, {3,KT,R},
            {2,LT,W}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,W},
                      {1,LB,G}, {1,ST,G}, {1,RB,G}
};

M mAWING = {                    {5,ST,G},                     {5,KT,R},
                                {4,ST,G},
            {3,LT,W}, {3,LB,W}, {3,ST,G}, {3,RB,W}, {3,RT,W}, {3,KT,R},
            {2,LT,G}, {2,LB,G}, {2,ST,G}, {2,RB,G}, {2,RT,G},
            {1,LT,W},                               {1,RT,W}
};

M mTIEIN = {                    {5,ST,W},                     {5,KT,R},
                                {4,ST,G},
            {3,LT,W}, {3,LB,W}, {3,ST,G}, {3,RB,W}, {3,RT,W}, {3,KT,R},
            {2,LT,G}, {2,LB,G}, {2,ST,G}, {2,RB,G}, {2,RT,G},
            {1,LT,W},                               {1,RT,W}
};

M mHK290 = {                    {4,ST,R},
                      {3,LB,R}, {3,ST,W}, {3,RB,R},
            {2,LT,W}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,W},
                      {1,LB,G}, {1,ST,G}, {1,RB,G}
};

M mLAMBD = {          {3,LB,R}, {3,ST,W}, {3,RB,R},
            {2,LT,R}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,R},
                      {1,LB,G}, {1,ST,G}, {1,RB,G},
                                {0,SY,R}
};

M mBWING = {                    {4,ST,R},
                      {3,LB,R}, {3,ST,W}, {3,RB,R},
            {2,LT,W}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,W}, {2,KT,R},
            {1,LT,R}, {1,LB,G}, {1,ST,G}, {1,RB,G}, {1,RT,R}
};

M mTIEBO = {                                                  {5,KT,R},
                                {4,ST,W},
            {3,LT,W}, {3,LB,W}, {3,ST,G}, {3,RB,W}, {3,RT,W},
            {2,LT,R}, {2,LB,G}, {2,ST,G}, {2,RB,G}, {2,RT,R},
                      {1,LB,W}, {1,ST,G}, {1,RB,W}
};

M mZ95HH = {                    {4,ST,W},
            {3,LT,W}, {3,LB,W}, {3,ST,W}, {3,RB,W}, {3,RT,W}, {3,KT,R},
            {2,LT,W}, {2,LB,G}, {2,ST,G}, {2,RB,G}, {2,RT,W},
                      {1,LB,W}, {1,ST,G}, {1,RB,W}
};

M mTIEDE = {                    {5,ST,G},
                                {4,ST,G},                     {4,KT,W},
            {3,LT,W}, {3,LB,W}, {3,ST,G}, {3,RB,W}, {3,RT,W},
            {2,LT,R}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,R},
            {1,LT,R}, {1,LB,W},           {1,RB,W}, {1,RT,R}
};

M mEWING = {                    {5,ST,W},
                                {4,ST,W},                     {4,KT,R},
            {3,LT,W}, {3,LB,W}, {3,ST,G}, {3,RB,W}, {3,RT,W}, {3,KT,R},
            {2,LT,W}, {2,LB,G}, {2,ST,G}, {2,RB,G}, {2,RT,W},
                      {1,LB,W}, {1,ST,G}, {1,RB,W}
};

M mTIEPH = {                    {4,ST,W},                     {4,KT,R},
            {3,LT,W}, {3,LB,W}, {3,ST,G}, {3,RB,W}, {3,RT,W}, {3,KT,R},
            {2,LT,W}, {2,LB,G}, {2,ST,G}, {2,RB,G}, {2,RT,W},
            {1,LT,W},                               {1,RT,W}
};

M mYT240 = {                    {4,ST,W},                     {4,KT,R},
            {3,LT,W}, {3,LB,W}, {3,ST,W}, {3,RB,W}, {3,RT,W},
            {2,LT,W}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,W},
            {1,LT,W}, {1,LB,G}, {1,ST,G}, {1,RB,G}, {1,RT,W}
};

M mVT49D = {                    {4,ST,W},
            {3,LT,W}, {3,LB,W}, {3,ST,G}, {3,RB,W}, {3,RT,W},
            {2,LT,W}, {2,LB,G}, {2,ST,G}, {2,RB,G}, {2,RT,W},
                      {1,LB,W}, {1,ST,W}, {1,RB,W}
};



#define MT  Upg::Modification,Upg::Title

std::list<Pilot> Pilot::pilots = {
  // faction         base size         name                        short                    xws                       ship                          xws                       gly  maneuv unique ps at ag hu sh cst actions                                                 upgrades
  { Faction::Rebel,  BaseSize::Small, "Luke Skywalker",           "Luke",                  "lukeskywalker",          "X-Wing",                     "xwing",                   "w", mXWING, true,  8, 3, 2, 3, 2, 28, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Biggs Darklighter",        "Biggs",                 "biggsdarklighter",       "X-Wing",                     "xwing",                   "w", mXWING, true,  5, 3, 2, 3, 2, 25, Act::Focus|Act::TargetLock,                            {MT,             Upg::Torpedo, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Red Squadron Pilot",       "Red Sq. Pilot",         "redsquadronpilot",       "X-Wing",                     "xwing",                   "w", mXWING, false, 4, 3, 2, 3, 2, 23, Act::Focus|Act::TargetLock,                            {MT,             Upg::Torpedo, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Rookie Pilot",             "Rookie Pilot",          "rookiepilot",            "X-Wing",                     "xwing",                   "w", mXWING, false, 2, 3, 2, 3, 2, 21, Act::Focus|Act::TargetLock,                            {MT,             Upg::Torpedo, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Wedge Antilles",           "Wedge",                 "wedgeantilles",          "X-Wing",                     "xwing",                   "w", mXWING, true,  9, 3, 2, 3, 2, 29, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Garven Dreis",             "Garven",                "garvendreis",            "X-Wing",                     "xwing",                   "w", mXWING, true,  6, 3, 2, 3, 2, 26, Act::Focus|Act::TargetLock,                            {MT,             Upg::Torpedo, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "\"Hobbie\" Klivian",       "Hobbie",                "hobbieklivian",          "X-Wing",                     "xwing",                   "w", mXWING, true,  5, 3, 2, 3, 2, 25, Act::Focus|Act::TargetLock,                            {MT,             Upg::Torpedo, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Jek Porkins",              "Porkins",               "jekporkins",             "X-Wing",                     "xwing",                   "w", mXWING, true,  7, 3, 2, 3, 2, 26, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Tarn Mison",               "Tarn Mison",            "tarnmison",              "X-Wing",                     "xwing",                   "w", mXWING, true,  3, 3, 2, 3, 2, 23, Act::Focus|Act::TargetLock,                            {MT,             Upg::Torpedo, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Wes Janson",               "Wes Janson",            "wasjanson",              "X-Wing",                     "xwing",                   "w", mXWING, true,  8, 3, 2, 3, 2, 29, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech} },

  { Faction::Empire, BaseSize::Small, "\"Mauler Mithel\"",        "Mauler Mithel",         "maulermithel",           "TIE Fighter",                "tiefighter",              "F", mTIEFI, true,  7, 2, 3, 3, 0, 17, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "\"Dark Curse\"",           "Dark Curse",            "darkcurse",              "TIE Fighter",                "tiefighter",              "F", mTIEFI, true,  6, 2, 3, 3, 0, 16, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, } },
  { Faction::Empire, BaseSize::Small, "\"Night Beast\"",          "Night Beast",           "nightbeast",             "TIE Fighter",                "tiefighter",              "F", mTIEFI, true,  5, 2, 3, 3, 0, 15, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, } },
  { Faction::Empire, BaseSize::Small, "Black Squadron Pilot",     "Black Sq. Plt",         "blacksquadronpilot",     "TIE Fighter",                "tiefighter",              "F", mTIEFI, false, 4, 2, 3, 3, 0, 14, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "Obsidian Squadron Pilot",  "Obsidian Sq. Plt",      "obsidiansquadronpilot",  "TIE Fighter",                "tiefighter",              "F", mTIEFI, false, 3, 2, 3, 3, 0, 13, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, } },
  { Faction::Empire, BaseSize::Small, "Academy Pilot",            "Academy Plt",           "academypilot",           "TIE Fighter",                "tiefighter",              "F", mTIEFI, false, 1, 2, 3, 3, 0, 12, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, } },
  { Faction::Empire, BaseSize::Small, "\"Howlrunner\"",           "Howlrunner",            "howlrunner",             "TIE Fighter",                "tiefighter",              "F", mTIEFI, true,  8, 2, 3, 3, 0, 18, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "\"Backstabber\"",          "Backstabber",           "backstabber",            "TIE Fighter",                "tiefighter",              "F", mTIEFI, true,  6, 2, 3, 3, 0, 16, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, } },
  { Faction::Empire, BaseSize::Small, "\"Winged Gundark\"",       "Winged Gundark",        "wingedgundark",          "TIE Fighter",                "tiefighter",              "F", mTIEFI, true,  5, 2, 3, 3, 0, 15, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, } },
  { Faction::Empire, BaseSize::Small, "\"Scourge\"",              "Scourge",               "scourge",                "TIE Fighter",                "tiefighter",              "F", mTIEFI, true,  7, 2, 3, 3, 0, 17, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "\"Wampa\"",                "Wampa",                 "wampa",                  "TIE Fighter",                "tiefighter",              "F", mTIEFI, true,  4, 2, 3, 3, 0, 14, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, } },
  { Faction::Empire, BaseSize::Small, "\"Youngster\"",            "Youngster",             "youngster",              "TIE Fighter",                "tiefighter",              "F", mTIEFI, true,  6, 2, 3, 3, 0, 15, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "\"Chaser\"",               "Chaser",                "chaser",                 "TIE Fighter",                "tiefighter",              "F", mTIEFI, true,  3, 2, 3, 3, 0, 14, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, } },

  { Faction::Rebel,  BaseSize::Small, "Horton Salm",              "Horton Salm",           "hortonsalm",             "Y-Wing",                     "ywing",                   "y", mYWING, true,  8, 2, 1, 5, 3, 25, Act::Focus|Act::TargetLock,                            {MT, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "\"Dutch\" Vander",         "Dutch Vander",          "dutchvander",            "Y-Wing",                     "ywing",                   "y", mYWING, true,  6, 2, 1, 5, 3, 23, Act::Focus|Act::TargetLock,                            {MT, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Gray Squadron Pilot",      "Gray Sq. Plt",          "graysquadronpilot",      "Y-Wing",                     "ywing",                   "y", mYWING, false, 4, 2, 1, 5, 3, 20, Act::Focus|Act::TargetLock,                            {MT, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Gold Squadron Pilot",      "Gold Sq. Plt",          "goldsquadronpilot",      "Y-Wing",                     "ywing",                   "y", mYWING, false, 2, 2, 1, 5, 3, 18, Act::Focus|Act::TargetLock,                            {MT, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Astromech} },

  { Faction::Empire, BaseSize::Small, "Darth Vader",              "Darth Vader",           "darthvader",             "TIE Advanced",               "tieadvanced",             "A", mTIEAD, true,  9, 2, 3, 3, 2, 29, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Maarek Stele",             "Maarek Steele",         "maarekstele",            "TIE Advanced",               "tieadvanced",             "A", mTIEAD, true,  7, 2, 3, 3, 2, 27, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Storm Squadron Pilot",     "Storm Sq. Plt",         "stormsquadronpilot",     "TIE Advanced",               "tieadvanced",             "A", mTIEAD, false, 4, 2, 3, 3, 2, 23, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,             Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Tempest Squadron Pilot",   "Tempest Sq. Plt",       "tempestsquadronpilot",   "TIE Advanced",               "tieadvanced",             "A", mTIEAD, false, 2, 2, 3, 3, 2, 21, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,             Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Zertik Strom",             "Zertik Strom",          "zertikstrom",            "TIE Advanced",               "tieadvanced",             "A", mTIEAD, true,  6, 2, 3, 3, 2, 26, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Juno Eclipse",             "Juno Eclipse",          "junoeclipse",            "TIE Advanced",               "tieadvanced",             "A", mTIEAD, true,  8, 2, 3, 3, 2, 28, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Commander Alozen",         "Cmdr. Alozen",          "commanderalozen",        "TIE Advanced",               "tieadvanced",             "A", mTIEAD, true,  5, 2, 3, 3, 2, 25, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Lieutenant Colzet",        "Lt. Colzet",            "lieutenantcolzet",       "TIE Advanced",               "tieadvanced",             "A", mTIEAD, true,  3, 2, 3, 3, 2, 23, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,             Upg::Missile} },

  { Faction::Rebel,  BaseSize::Large, "Han Solo",                 "Han Solo",              "hansolo",                "YT-1300",                    "yt1300",                  "m", mYT130, true,  9, 3, 1, 8, 5, 46, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Lando Calrissian",         "Lando",                 "landocalrissian",        "YT-1300",                    "yt1300",                  "m", mYT130, true,  7, 3, 1, 8, 5, 44, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Chewbacca",                "Chewbacca",             "chewbacca",              "YT-1300",                    "yt1300",                  "m", mYT130, true,  5, 3, 1, 8, 5, 42, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Outer Rim Smuggler",       "Outer Rim Smug",        "outerrimsmuggler",       "YT-1300",                    "yt1300",                  "m", mYT130, false, 1, 2, 1, 6, 4, 27, Act::Focus|Act::TargetLock,                            {MT,             Upg::Missile, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Han Solo",                 "Han Solo",              "hansolo-swx57",          "YT-1300",                    "yt1300",                  "m", mYT130, true,  9, 3, 1, 8, 5, 46, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Rey",                      "Rey",                   "rey",                    "YT-1300",                    "yt1300",                  "m", mYT130, true,  8, 3, 1, 8, 5, 45, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Chewbacca",                "Chewbacca",             "chewbacca-swx57",        "YT-1300",                    "yt1300",                  "m", mYT130, true,  5, 3, 1, 8, 5, 42, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Resistance Sympathizer",   "Res Sympathizer",       "resistancesympathizer",  "YT-1300",                    "yt1300",                  "m", mYT130, false, 3, 3, 1, 8, 5, 38, Act::Focus|Act::TargetLock,                            {MT,             Upg::Missile, Upg::Crew, Upg::Crew} },

  { Faction::Empire, BaseSize::Large, "Boba Fett",                "Boba Fett",             "bobafett",               "Firespray-31",               "firespray31",             "f", mFSP31, true,  8, 3, 2, 6, 4, 39, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::Elite, Upg::Cannon, Upg::Bomb, Upg::Crew, Upg::Missile} },
  { Faction::Empire, BaseSize::Large, "Kath Scarlet",             "Kath Scarlet",          "kathscarlet",            "Firespray-31",               "firespray31",             "f", mFSP31, true,  7, 3, 2, 6, 4, 38, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::Elite, Upg::Cannon, Upg::Bomb, Upg::Crew, Upg::Missile} },
  { Faction::Empire, BaseSize::Large, "Krassis Trelix",           "Krasses Trelix",        "krassistrelix",          "Firespray-31",               "firespray31",             "f", mFSP31, true,  5, 3, 2, 6, 4, 36, Act::Focus|Act::TargetLock|Act::Evade,                 {MT,             Upg::Cannon, Upg::Bomb, Upg::Crew, Upg::Missile} },
  { Faction::Empire, BaseSize::Large, "Bounty Hunter",            "Bounty Hunter",         "bountyhunter",           "Firespray-31",               "firespray31",             "f", mFSP31, false, 3, 3, 2, 6, 4, 33, Act::Focus|Act::TargetLock|Act::Evade,                 {MT,             Upg::Cannon, Upg::Bomb, Upg::Crew, Upg::Missile} },

  { Faction::Rebel,  BaseSize::Small, "Tycho Celchu",             "Tycho Celchu",          "tychocelchu",            "A-Wing",                     "awing",                   "a", mAWING, true,  8, 2, 3, 2, 2, 26, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT, Upg::Elite, Upg::Missile} },
  { Faction::Rebel,  BaseSize::Small, "Arvel Crynyd",             "Arvel Crynyd",          "arvelcrynyd",            "A-Wing",                     "awing",                   "a", mAWING, true,  6, 2, 3, 2, 2, 23, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT,             Upg::Missile} },
  { Faction::Rebel,  BaseSize::Small, "Green Squadron Pilot",     "Green Sq. Pilot",       "greensquadronpilot",     "A-Wing",                     "awing",                   "a", mAWING, false, 3, 2, 3, 2, 2, 19, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT, Upg::Elite, Upg::Missile} },
  { Faction::Rebel,  BaseSize::Small, "Prototype Pilot",          "Prototype Pilot",       "prototypepilot",         "A-Wing",                     "awing",                   "a", mAWING, false, 1, 2, 3, 2, 2, 17, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT,             Upg::Missile} },
  { Faction::Rebel,  BaseSize::Small, "Jake Farrell",             "Jake Farrell",          "jakefarrell",            "A-Wing",                     "awing",                   "a", mAWING, true , 7, 2, 3, 2, 2, 24, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT, Upg::Elite, Upg::Missile} },
  { Faction::Rebel,  BaseSize::Small, "Gemmer Sojan",             "Gemmer Sojan",          "gennersojan",            "A-Wing",                     "awing",                   "a", mAWING, true , 5, 2, 3, 2, 2, 22, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT,             Upg::Missile} },

  { Faction::Empire, BaseSize::Small, "Soontir Fel",              "Soontir Fel",           "soontirfel",             "TIE Interceptor",            "tieinterceptor",          "I", mTIEIN, true,  9, 3, 3, 3, 0, 27, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "Turr Phennir",             "Turr Phennir",          "turrphennir",            "TIE Interceptor",            "tieinterceptor",          "I", mTIEIN, true,  7, 3, 3, 3, 0, 25, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "\"Fel's Wrath\"",          "Fel's Wrath",           "felswrath",              "TIE Interceptor",            "tieinterceptor",          "I", mTIEIN, true,  5, 3, 3, 3, 0, 23, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT,           } },
  { Faction::Empire, BaseSize::Small, "Saber Squadron Pilot",     "Saber Sq. Pilot",       "sabersquadronpilot",     "TIE Interceptor",            "tieinterceptor",          "I", mTIEIN, false, 4, 3, 3, 3, 0, 21, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "Avenger Squadron Pilot",   "Avenger Sq. Pilot",     "avengersquadronpilot",   "TIE Interceptor",            "tieinterceptor",          "I", mTIEIN, false, 3, 3, 3, 3, 0, 20, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT,           } },
  { Faction::Empire, BaseSize::Small, "Alpha Squadron Pilot",     "Alpha Sq. Pilot",       "alphasquadronpilot",     "TIE Interceptor",            "tieinterceptor",          "I", mTIEIN, false, 1, 3, 3, 3, 0, 18, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT,           } },
  { Faction::Empire, BaseSize::Small, "Carnor Jax",               "Carnor Jax",            "carnorjax",              "TIE Interceptor",            "tieinterceptor",          "I", mTIEIN, true,  8, 3, 3, 3, 0, 26, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "Tetran Cowall",            "Tetran Cowall",         "tetrancowell",           "TIE Interceptor",            "tieinterceptor",          "I", mTIEIN, true,  7, 3, 3, 3, 0, 24, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "Kir Kanos",                "Kir Kanos",             "kirkanos",               "TIE Interceptor",            "tieinterceptor",          "I", mTIEIN, true,  6, 3, 3, 3, 0, 24, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT,           } },
  { Faction::Empire, BaseSize::Small, "Lieutenant Lorrir",        "Lt. Lorrir",            "lieutenantlorrir",       "TIE Interceptor",            "tieinterceptor",          "I", mTIEIN, true,  5, 3, 3, 3, 0, 23, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT,           } },
  { Faction::Empire, BaseSize::Small, "Royal Guard Pilot",        "Royal Guard Pilot",     "royalguardpilot",        "TIE Interceptor",            "tieinterceptor",          "I", mTIEIN, false, 6, 3, 3, 3, 0, 22, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT, Upg::Elite} },

  { Faction::Rebel,  BaseSize::Small, "Jan Ors",                  "Jan Ors",               "janors",                 "HWK-290",                    "hwk290",                  "h", mHK290, true,  8, 1, 2, 4, 1, 25, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Cannon, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Small, "Kyle Katarn",              "Kyle Katarn",           "kylekatarn",             "HWK-290",                    "hwk290",                  "h", mHK290, true,  6, 1, 2, 4, 1, 21, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Cannon, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Small, "Roark Garnet",             "Roark Garnet",          "roarkgarnet",            "HWK-290",                    "hwk290",                  "h", mHK290, true,  4, 1, 2, 4, 1, 19, Act::Focus|Act::TargetLock,                            {MT,             Upg::Cannon, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Small, "Rebel Operative",          "Rebel Operative",       "rebeloperative",         "HWK-290",                    "hwk290",                  "h", mHK290, false, 2, 1, 2, 4, 1, 16, Act::Focus|Act::TargetLock,                            {MT,             Upg::Cannon, Upg::Crew} },

  { Faction::Empire, BaseSize::Large, "Captain Kagi",             "Capt. Kagi",            "captainkagi",            "Lambda-class Shuttle",       "lambdaclassshuttle",      "l", mLAMBD, true,  8, 3, 1, 5, 5, 27, Act::Focus|Act::TargetLock,                            {MT, Upg::System, Upg::Cannon, Upg::Crew, Upg::Crew} },
  { Faction::Empire, BaseSize::Large, "Captain Yorr",             "Capt. Yorr",            "captainyorr",            "Lambda-class Shuttle",       "lambdaclassshuttle",      "l", mLAMBD, true,  4, 3, 1, 5, 5, 24, Act::Focus|Act::TargetLock,                            {MT, Upg::System, Upg::Cannon, Upg::Crew, Upg::Crew} },
  { Faction::Empire, BaseSize::Large, "Colonel Jendon",           "Col. Jendon",           "coloneljendon",          "Lambda-class Shuttle",       "lambdaclassshuttle",      "l", mLAMBD, true,  6, 3, 1, 5, 5, 26, Act::Focus|Act::TargetLock,                            {MT, Upg::System, Upg::Cannon, Upg::Crew, Upg::Crew} },
  { Faction::Empire, BaseSize::Large, "Omicron Group Pilot",      "Omicron Grp Pilot",     "omicrongrouppilot",      "Lambda-class Shuttle",       "lambdaclassshuttle",      "l", mLAMBD, false, 2, 3, 1, 5, 5, 21, Act::Focus|Act::TargetLock,                            {MT, Upg::System, Upg::Cannon, Upg::Crew, Upg::Crew} },

  { Faction::Rebel,  BaseSize::Small, "Ten Numb",                 "Ten Numb",              "tennumb",                "B-Wing",                     "bwing",                   "b", mBWING, true,  8, 3, 1, 3, 5, 31, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Torpedo, Upg::Torpedo} },
  { Faction::Rebel,  BaseSize::Small, "Ibtisam",                  "Ibtisam",               "ibtisam",                "B-Wing",                     "bwing",                   "b", mBWING, true,  6, 3, 1, 3, 5, 28, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Torpedo, Upg::Torpedo} },
  { Faction::Rebel,  BaseSize::Small, "Dagger Squadron Pilot",    "Dagger Sq. Pilot",      "daggersquadronpilot",    "B-Wing",                     "bwing",                   "b", mBWING, false, 4, 3, 1, 3, 5, 24, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Torpedo, Upg::Torpedo} },
  { Faction::Rebel,  BaseSize::Small, "Blue Squadron Pilot",      "Blue Sq. Pilot",        "bluesquadronpilot",      "B-Wing",                     "bwing",                   "b", mBWING, false, 2, 3, 1, 3, 5, 22, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Torpedo, Upg::Torpedo} },
  { Faction::Rebel,  BaseSize::Small, "Keyan Farlander",          "Keyan Farlander",       "keyanfarlander",         "B-Wing",                     "bwing",                   "b", mBWING, true,  7, 3, 1, 3, 5, 29, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Torpedo, Upg::Torpedo} },
  { Faction::Rebel,  BaseSize::Small, "Nera Dantels",             "Nera Dantels",          "neradantels",            "B-Wing",                     "bwing",                   "b", mBWING, true,  5, 3, 1, 3, 5, 26, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Torpedo, Upg::Torpedo} },

  { Faction::Empire, BaseSize::Small, "Major Rhymer",             "Maj. Rhymer",           "majorrhymer",            "TIE Bomber",                 "tiebomber",               "B", mTIEBO, true,  7, 2, 2, 6, 0, 26, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb} },
  { Faction::Empire, BaseSize::Small, "Captain Jonus",            "Capt. Jonus",           "captainjonus",           "TIE Bomber",                 "tiebomber",               "B", mTIEBO, true,  6, 2, 2, 6, 0, 22, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb} },
  { Faction::Empire, BaseSize::Small, "Gamma Squadron Pilot",     "Gamma Sq. Pilot",       "gammasquadronpilot",     "TIE Bomber",                 "tiebomber",               "B", mTIEBO, false, 4, 2, 2, 6, 0, 18, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT,             Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb} },
  { Faction::Empire, BaseSize::Small, "Schimitar Squadron Pilot", "Schimitar Sq. Pilot",   "schimitarsquadronpilot", "TIE Bomber",                 "tiebomber",               "B", mTIEBO, false, 2, 2, 2, 6, 0, 16, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT,             Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb} },
  { Faction::Empire, BaseSize::Small, "Tomax Bren",               "Tomax Bren",            "tomaxbren",              "TIE Bomber",                 "tiebomber",               "B", mTIEBO, true,  8, 2, 2, 6, 0, 24, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb} },
  { Faction::Empire, BaseSize::Small, "\"Deathfire\"",            "Deathfire",             "deathfire",              "TIE Bomber",                 "tiebomber",               "B", mTIEBO, true,  3, 2, 2, 6, 0, 17, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT,             Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb} },
  { Faction::Empire, BaseSize::Small, "Gamma Squadron Veteran",   "Gamma Sq. Vet.",        "gammasquadronveteran",   "TIE Bomber",                 "tiebomber",               "B", mTIEBO, false, 5, 2, 2, 6, 0, 19, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb} },

  { Faction::Rebel,  BaseSize::Small, "Airen Cracken",            "Airen Cracken",         "airencracken",           "Z-95 Headhunter",            "z95headhunter",           "z", mZ95HH, true,  8, 2, 2, 2, 2, 19, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile} },
  { Faction::Rebel,  BaseSize::Small, "Lieutenant Blount",        "Lt. Blount",            "lieutenantblout",        "Z-95 Headhunter",            "z95headhunter",           "z", mZ95HH, true,  6, 2, 2, 2, 2, 17, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile} },
  { Faction::Rebel,  BaseSize::Small, "Tala Squadron Pilot",      "Tala Sq. Pilot",        "talasquadronpilot",      "Z-95 Headhunter",            "z95headhunter",           "z", mZ95HH, false, 4, 2, 2, 2, 2, 13, Act::Focus|Act::TargetLock,                            {MT,             Upg::Missile} },
  { Faction::Rebel,  BaseSize::Small, "Bandit Squadron Pilot",    "Bandit Sq. Pilot",      "banditsquadronpilot",    "Z-95 Headhunter",            "z95headhunter",           "z", mZ95HH, false, 2, 2, 2, 2, 2, 12, Act::Focus|Act::TargetLock,                            {MT,             Upg::Missile} },

  { Faction::Empire, BaseSize::Small, "Rexler Brath",             "Rexler Brath",          "rexlerbrath",            "TIE Defender",               "tiedefender",             "D", mTIEDE, true,  8, 3, 3, 3, 3, 37, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Cannon, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Colonel Vessery",          "Col. Vessery",          "colonelvessery",         "TIE Defender",               "tiedefender",             "D", mTIEDE, true,  6, 3, 3, 3, 3, 35, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Cannon, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Onyx Squadron Pilot",      "Onyx Sq. Pilot",        "onyxsquadronpilot",      "TIE Defender",               "tiedefender",             "D", mTIEDE, false, 3, 3, 3, 3, 3, 32, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT,             Upg::Cannon, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Delta Squadron Pilot",     "Delta Sq. Pilot",       "deltasquadronpilot",     "TIE Defender",               "tiedefender",             "D", mTIEDE, false, 1, 3, 3, 3, 3, 30, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT,             Upg::Cannon, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Maarek Stele",             "Maarek Steele",         "maarekstele",            "TIE Defender",               "tiedefender",             "D", mTIEDE, true,  7, 3, 3, 3, 3, 35, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Cannon, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Countess Ryad",            "Countess Ryad",         "countessryad",           "TIE Defender",               "tiedefender",             "D", mTIEDE, true,  5, 3, 3, 3, 3, 34, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Cannon, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Glaive Squadron Pilot",    "Glaive Sq. Pilot",      "glaivesquadronpilot",    "TIE Defender",               "tiedefender",             "D", mTIEDE, false, 6, 3, 3, 3, 3, 34, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Cannon, Upg::Missile} },

  { Faction::Rebel,  BaseSize::Small, "Corran Horn",              "Corran Horn",           "corranhorn",             "E-Wing",                     "ewing",                   "e", mEWING, true,  8, 3, 3, 2, 3, 35, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::System, Upg::Torpedo, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Etahn A'baht",             "Etahn A'baht",          "etahnabaht",             "E-Wing",                     "ewing",                   "e", mEWING, true,  5, 3, 3, 2, 3, 32, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::System, Upg::Torpedo, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Blackmoon Squadron Pilot", "Blackmoon Sq. Pilot",   "blackmoonsquadronpilot", "E-Wing",                     "ewing",                   "e", mEWING, false, 3, 3, 3, 2, 3, 29, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,             Upg::System, Upg::Torpedo, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Knave Squadron Pilot",     "Knave Sq. Pilot",       "knavesquadronpilot",     "E-Wing",                     "ewing",                   "e", mEWING, false, 1, 3, 3, 2, 3, 27, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,             Upg::System, Upg::Torpedo, Upg::Astromech} },

  { Faction::Empire, BaseSize::Small, "\"Whisper\"",              "Whisper",               "whisper",                "TIE Phantom",                "tiephantom",              "P", mTIEPH, true,  7, 4, 2, 2, 2, 32, Act::Focus|Act::BarrelRoll|Act::Evade|Act::Cloak,      {MT, Upg::Elite, Upg::System, Upg::Crew} },
  { Faction::Empire, BaseSize::Small, "\"Echo\"",                 "Echo",                  "echo",                   "TIE Phantom",                "tiephantom",              "P", mTIEPH, true,  6, 4, 2, 2, 2, 30, Act::Focus|Act::BarrelRoll|Act::Evade|Act::Cloak,      {MT, Upg::Elite, Upg::System, Upg::Crew} },
  { Faction::Empire, BaseSize::Small, "Shadow Squadron Pilot",    "Shadow Sq. Pilot",      "shadowsquadronpilot",    "TIE Phantom",                "tiephantom",              "P", mTIEPH, false, 5, 4, 2, 2, 2, 27, Act::Focus|Act::BarrelRoll|Act::Evade|Act::Cloak,      {MT,             Upg::System, Upg::Crew} },
  { Faction::Empire, BaseSize::Small, "Sigma Squadron Pilot",     "Signa Sq. Pilot",       "sigmasquadronpilot",     "TIE Phantom",                "tiephantom",              "P", mTIEPH, false, 3, 4, 2, 2, 2, 25, Act::Focus|Act::BarrelRoll|Act::Evade|Act::Cloak,      {MT,             Upg::System, Upg::Crew} },

  { Faction::Rebel,  BaseSize::Large, "Dash Rendar",              "Dash Rendar",           "dashrendar",             "YT-2400 Freighter",          "yt2400",                  "o", mYT240, true,  7, 2, 2, 5, 5, 36, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Cannon, Upg::Missile, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "\"Leebo\"",                "Leebo",                 "leebo",                  "YT-2400 Freighter",          "yt2400",                  "o", mYT240, true,  5, 2, 2, 5, 5, 34, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Cannon, Upg::Missile, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Eaden Vrill",              "Eaden Vrill",           "eadenvrill",             "YT-2400 Freighter",          "yt2400",                  "o", mYT240, true,  3, 2, 2, 5, 5, 32, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT,             Upg::Cannon, Upg::Missile, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Wild Space Fringer",       "Wild Space Fringer",    "wildspacefringer",       "YT-2400 Freighter",          "yt2400",                  "o", mYT240, false, 2, 2, 2, 5, 5, 30, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT,             Upg::Cannon, Upg::Missile, Upg::Crew} },

  { Faction::Empire, BaseSize::Large, "Rear Admiral Chiraneau",   "RADM. Chiraneau",       "rearadmiralchiraneau",   "VT-49 Decimator",            "vt49decimator",           "d", mVT49D, true,  8, 3, 0,12, 4, 46, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Torpedo, Upg::Crew, Upg::Crew, Upg::Crew, Upg::Bomb} },
  { Faction::Empire, BaseSize::Large, "Commander Kenkirk",        "Cmdr. Kenkirk",         "commanderkenkirk",       "VT-49 Decimator",            "vt49decimator",           "d", mVT49D, true,  6, 3, 0,12, 4, 44, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Torpedo, Upg::Crew, Upg::Crew, Upg::Crew, Upg::Bomb} },
  { Faction::Empire, BaseSize::Large, "Captain Oicunn",           "Capt Oicunn",           "captainoicunn",          "VT-49 Decimator",            "vt49decimator",           "d", mVT49D, true,  4, 3, 0,12, 4, 42, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Torpedo, Upg::Crew, Upg::Crew, Upg::Crew, Upg::Bomb} },
  { Faction::Empire, BaseSize::Large, "Patrol Leader",            "Patrol Leader",         "patrolleader",           "VT-49 Decimator",            "vt49decimator",           "d", mVT49D, false, 3, 3, 0,12, 4, 40, Act::Focus|Act::TargetLock,                            {MT,             Upg::Torpedo, Upg::Crew, Upg::Crew, Upg::Crew, Upg::Bomb} },
/*
  { Faction::Scum,   BaseSize::Small, "Kavil",                    "Kavil",                 "kavil",                  "Y-Wing",                     "ywing",                   "y", true,  7, 2, 1, 5, 3, 24, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::SalvagedAstromech} },
  { Faction::Scum,   BaseSize::Small, "Drea Renthal",             "Drea Renthal",          "drearenthal",            "Y-Wing",                     "ywing",                   "y", true,  5, 2, 1, 5, 3, 22, Act::Focus|Act::TargetLock,                            {MT,             Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::SalvagedAstromech} },
  { Faction::Scum,   BaseSize::Small, "Hired Gun",                "Hired Gun",             "hiredgun",               "Y-Wing",                     "ywing",                   "y", false, 4, 2, 1, 5, 3, 20, Act::Focus|Act::TargetLock,                            {MT,             Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::SalvagedAstromech} },
  { Faction::Scum,   BaseSize::Small, "Syndicate Thug",           "Syndicate Thug",        "syndicatethug",          "Y-Wing",                     "ywing",                   "y", false, 2, 2, 1, 5, 3, 18, Act::Focus|Act::TargetLock,                            {MT,             Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::SalvagedAstromech} },

  { Faction::Scum,   BaseSize::Large, "Boba Fett",                "Boba Fett",             "bobafett",               "Firespray-31",               "firespray31",             "f", true,  8, 3, 2, 6, 4, 39, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::Elite, Upg::Cannon, Upg::Bomb, Upg::Crew, Upg::Missile, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Kath Scarlet",             "Kath Scarlet",          "kathscarlet",            "Firespray-31",               "firespray31",             "f", true,  7, 3, 2, 6, 4, 38, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::Elite, Upg::Cannon, Upg::Bomb, Upg::Crew, Upg::Missile, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Emon Azzameen",            "Emon Azzameen",         "emonazzameen",           "Firespray-31",               "firespray31",             "f", true,  6, 3, 2, 6, 4, 36, Act::Focus|Act::TargetLock|Act::Evade,                 {MT,             Upg::Cannon, Upg::Bomb, Upg::Crew, Upg::Missile, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Mandalorian Mercenary",    "Mandalorian Merc.",     "mandalorianmercenary",   "Firespray-31",               "firespray31",             "f", false, 5, 3, 2, 6, 4, 35, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::Elite, Upg::Cannon, Upg::Bomb, Upg::Crew, Upg::Missile, Upg::Illicit} },

  { Faction::Scum,   BaseSize::Small, "Dace Bonearm",             "Dace Bonearm",          "dacebonearm",            "HWK-290",                    "hwk290",                  "h", true,  7, 1, 2, 4, 1, 23, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Cannon, Upg::Crew, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Palob Godalhi",            "Palob Godalhi",         "palobgodalhi",           "HWK-290",                    "hwk290",                  "h", true,  5, 1, 2, 4, 1, 20, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Cannon, Upg::Crew, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Torkil Mux",               "Torkil Mux",            "torkilmux",              "HWK-290",                    "hwk290",                  "h", true,  3, 1, 2, 4, 1, 19, Act::Focus|Act::TargetLock,                            {MT,             Upg::Cannon, Upg::Crew, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Spice Runner",             "Spice Runner",          "spicerunner",            "HWK-290",                    "hwk290",                  "h", false, 1, 1, 2, 4, 1, 16, Act::Focus|Act::TargetLock,                            {MT,             Upg::Cannon, Upg::Crew, Upg::Illicit} },

  { Faction::Scum,   BaseSize::Small, "N'Dru Suhlak",             "N'Dru Suhlak",          "ndrusuhlak",             "Z-95 Headhunter",            "z95headhunter",           "z", true,  7, 2, 2, 2, 2, 17, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Kaa'to Leeachos",          "Kaa'to Leeachos",       "kaatoleeachos",          "Z-95 Headhunter",            "z95headhunter",           "z", true,  5, 2, 2, 2, 2, 15, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Black Sun Soldier",        "Black Sun Soldier",     "blacksunsoldier",        "Z-95 Headhunter",            "z95headhunter",           "z", false, 3, 2, 2, 2, 2, 13, Act::Focus|Act::TargetLock,                            {MT,             Upg::Missile, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Binayre Pirate",           "Binayre Pirate",        "binayrepirate",          "Z-95 Headhunter",            "z95headhunter",           "z", false, 1, 2, 2, 2, 2, 12, Act::Focus|Act::TargetLock,                            {MT,             Upg::Missile, Upg::Illicit} },

  { Faction::Scum,   BaseSize::Small, "Laetin A'shera",           "Laetin A'shera",        "laetinashera",           "M3-A Scyk Interceptor",      "m3ainterceptor",          "s", true,  6, 2, 3, 2, 1, 18, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,           } }, 
  { Faction::Scum,   BaseSize::Small, "Serissu",                  "Serissu",               "serissu",                "M3-A Scyk Interceptor",      "m3ainterceptor",          "s", true,  8, 2, 3, 2, 1, 20, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite} },
  { Faction::Scum,   BaseSize::Small, "Tansarii Point Veteran",   "Tansarii Point Vet.",   "tansariipointveteran",   "M3-A Scyk Interceptor",      "m3ainterceptor",          "s", false, 5, 2, 3, 2, 1, 17, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite} },
  { Faction::Scum,   BaseSize::Small, "Cartel Spacer",            "Cartel Spacer",         "cartelspacer",           "M3-A Scyk Interceptor",      "m3ainterceptor",          "s", false, 2, 2, 3, 2, 1, 14, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,           } },

  { Faction::Scum,   BaseSize::Small, "Prince Xizor",             "Prince Xizor",          "princexizor",            "StarViper",                  "starviper",               "v", true,  7, 3, 3, 4, 1, 31, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Torpedo} },
  { Faction::Scum,   BaseSize::Small, "Guri",                     "Guri",                  "guri",                   "StarViper",                  "starviper",               "v", true,  5, 3, 3, 4, 1, 30, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Torpedo} },
  { Faction::Scum,   BaseSize::Small, "Black Sun Vigo",           "Black Sun Vigo",        "blacksunvigo",           "StarViper",                  "starviper",               "v", false, 3, 3, 3, 4, 1, 27, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT,             Upg::Torpedo} },
  { Faction::Scum,   BaseSize::Small, "Black Sun Enforcer",       "Black Sun Enforcer",    "blacksunenforcer",       "StarViper",                  "starviper",               "v", false, 1, 3, 3, 4, 1, 25, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT,             Upg::Torpedo} },

  { Faction::Scum,   BaseSize::Large, "IG-88A",                   "IG-88A",                "ig88a",                  "IG-2000",                    "aggressor",               "i", true,  6, 3, 3, 4, 4, 36, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Cannon, Upg::Bomb, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "IG-88B",                   "IG-88B",                "ig88b",                  "IG-2000",                    "aggressor",               "i", true,  6, 3, 3, 4, 4, 36, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Cannon, Upg::Bomb, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "IG-88C",                   "IG-88C",                "ig88c",                  "IG-2000",                    "aggressor",               "i", true,  6, 3, 3, 4, 4, 36, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Cannon, Upg::Bomb, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "IG-88D",                   "IG-88D",                "ig88d",                  "IG-2000",                    "aggressor",               "i", true,  6, 3, 3, 4, 4, 36, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Cannon, Upg::Bomb, Upg::Illicit} },

  { Faction::Scum,   BaseSize::Large, "Bossk",                    "Bossk",                 "bossk",                  "YV-666 Freighter",           "yv666",                   "t", true,  7, 3, 1, 6, 6, 35, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Cannon, Upg::Missile, Upg::Crew, Upg::Crew, Upg::Crew, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Latts Razzi",              "Latts Razzi",           "lattsrazzi",             "YV-666 Freighter",           "yv666",                   "t", true,  5, 3, 1, 6, 6, 33, Act::Focus|Act::TargetLock,                            {MT,             Upg::Cannon, Upg::Missile, Upg::Crew, Upg::Crew, Upg::Crew, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Moralo Eval",              "Moralo Eval",           "moraloeval",             "YV-666 Freighter",           "yv666",                   "t", true,  6, 3, 1, 6, 6, 34, Act::Focus|Act::TargetLock,                            {MT,             Upg::Cannon, Upg::Missile, Upg::Crew, Upg::Crew, Upg::Crew, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Trandoshan Slaver",        "Trandoshan Slaver",     "trandoshanslaver",       "YV-666 Freighter",           "yv666",                   "t", false, 2, 3, 1, 6, 6, 29, Act::Focus|Act::TargetLock,                            {MT,             Upg::Cannon, Upg::Missile, Upg::Crew, Upg::Crew, Upg::Crew, Upg::Illicit} },

  { Faction::Scum,   BaseSize::Small, "Talonbane Cobra",          "Talonbane Cobra",       "talonbanecobra",         "Kihraxz Fighter",            "kihraxzfighter",          "r", true,  9, 3, 2, 4, 1, 28, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Graz the Hunter",          "Graz the Hunter",       "grazthehunter",          "Kihraxz Fighter",            "kihraxzfighter",          "r", true,  6, 3, 2, 4, 1, 25, Act::Focus|Act::TargetLock,                            {MT,             Upg::Missile, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Black Sun Ace",            "Black Sun Ace",         "blacksunace",            "Kihraxz Fighter",            "kihraxzfighter",          "r", false, 5, 3, 2, 4, 1, 23, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Cartel Marauder",          "Cartel Marauder",       "cartelmarauder",         "Kihraxz Fighter",            "kihraxzfighter",          "r", false, 2, 3, 2, 4, 1, 20, Act::Focus|Act::TargetLock,                            {MT,             Upg::Missile, Upg::Illicit} },

  { Faction::Rebel,  BaseSize::Small, "Miranda Doni",             "Miranda Doni",          "mirandadoni",            "K-Wing",                     "kwing",                   "k", true,  8, 2, 1, 5, 4, 29, Act::Focus|Act::TargetLock|Act::SLAM,                  {MT, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Crew, Upg::Bomb, Upg::Bomb} },
  { Faction::Rebel,  BaseSize::Small, "Esege Tuketu",             "Esege Tuketu",          "esegetuketu",            "K-Wing",                     "kwing",                   "k", true,  6, 2, 1, 5, 4, 28, Act::Focus|Act::TargetLock|Act::SLAM,                  {MT, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Crew, Upg::Bomb, Upg::Bomb} },
  { Faction::Rebel,  BaseSize::Small, "Guardian Squadron Pilot",  "Guardian Sq. Pilot",    "guardiansquadronpilot",  "K-Wing",                     "kwing",                   "k", false, 4, 2, 1, 5, 4, 25, Act::Focus|Act::TargetLock|Act::SLAM,                  {MT, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Crew, Upg::Bomb, Upg::Bomb} },
  { Faction::Rebel,  BaseSize::Small, "Warden Squadron Pilot",    "Warden Sq. Pilot",      "wardensquadronpilot",    "K-Wing",                     "kwing",                   "k", false, 2, 2, 1, 5, 4, 23, Act::Focus|Act::TargetLock|Act::SLAM,                  {MT, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Crew, Upg::Bomb, Upg::Bomb} },

  { Faction::Empire, BaseSize::Small, "\"Redline\"",              "Redline",               "redline",                "TIE Punisher",               "tiepunisher",             "N", true,  7, 2, 1, 6, 3, 27, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::System, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb, Upg::Bomb} },
  { Faction::Empire, BaseSize::Small, "\"Deathrain\"",            "Deathrain",             "deathrain",              "TIE Punisher",               "tiepunisher",             "N", true,  6, 2, 1, 6, 3, 26, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::System, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb, Upg::Bomb} },
  { Faction::Empire, BaseSize::Small, "Black Eight Sq. Pilot",    "Black Eight Sq. Pilot", "blackeightsqpilot",      "TIE Punisher",               "tiepunisher",             "N", false, 4, 2, 1, 6, 3, 23, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::System, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb, Upg::Bomb} },
  { Faction::Empire, BaseSize::Small, "Cutlass Squadron Pilot",   "Cutlass Sq. Pilot",     "cutlasssquadronpilot",   "TIE Punisher",               "tiepunisher",             "N", false, 2, 2, 1, 6, 3, 21, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::System, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb, Upg::Bomb} },

  { Faction::Rebel,  BaseSize::Large, "Hera Syndulla",            "Hera Syndulla",         "herasyndulla",           "VCX-100",                    "vcx100",                  "G", true,  7, 4, 0,10, 6, 40, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::System, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Kanan Jarrus",             "Kanan Jarrus",          "kananjarrus",            "VCX-100",                    "vcx100",                  "G", true,  5, 4, 0,10, 6, 38, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::System, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "\"Chopper\"",              "Chopper",               "chopper",                "VCX-100",                    "vcx100",                  "G", true,  4, 4, 0,10, 6, 37, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::System, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Lothal Rebel",             "Lothal Rebel",          "lothalrebel",            "VCX-100",                    "vcx100",                  "G", false, 3, 4, 0,10, 6, 35, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::System, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Crew, Upg::Crew} },

  { Faction::Rebel,  BaseSize::Small, "Hera Syndulla",            "Hera Syndula",          "herasyndulla",           "Attack Shuttle",             "attackshuttle",           "g", true,  7, 3, 2, 2, 2, 22, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite, Upg::Turret, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Small, "Sabine Wren",              "Sabine Wren",           "sabinewren",             "Attack Shuttle",             "attackshuttle",           "g", true,  5, 3, 2, 2, 2, 21, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite, Upg::Turret, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Small, "Ezra Bridger",             "Ezra Bridger",          "ezrabridger",            "Attack Shuttle",             "attackshuttle",           "g", true,  4, 3, 2, 2, 2, 20, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite, Upg::Turret, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Small, "\"Zeb\" Orrelios",         "Zeb Orrelios",          "zeborrelios",            "Attack Shuttle",             "attackshuttle",           "g", true,  3, 3, 2, 2, 2, 18, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT,             Upg::Turret, Upg::Crew} },

  { Faction::Empire, BaseSize::Small, "The Inquisitor",           "The Inquisitor",         "theinquisitor",          "TIE Advanced Prototype",     "tieadvancedprototype",    "R", true,  8, 2, 3, 2, 2, 25, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Valen Rudor",              "Valen Rudor",            "valenrudor",             "TIE Advanced Prototype",     "tieadvancedprototype",    "R", true,  6, 2, 3, 2, 2, 22, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Baron of the Empire",      "Baron of the Empire",    "baronoftheempire",       "TIE Advanced Prototype",     "tieadvancedprototype",    "R", false, 4, 2, 3, 2, 2, 19, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Sienar Test Pilot",        "Sienar Test Pilot",      "sienartestpilot",        "TIE Advanced Prototype",     "tieadvancedprototype",    "R", false, 2, 2, 3, 2, 2, 16, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT,             Upg::Missile} },

  { Faction::Scum,   BaseSize::Small, "Zuckuss",                  "Zuckuss",                "zuckuss",                "G-1A Starfighter",           "g1astarfighter",          "n", true,  7, 3, 1, 4, 4, 28, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::Elite, Upg::Crew, Upg::System, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "4-LOM",                    "4-LOM",                  "4lom",                   "G-1A Starfighter",           "g1astarfighter",          "n", true,  6, 3, 1, 4, 4, 27, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::Elite, Upg::Crew, Upg::System, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Gand Findsman",            "Gand Findsman",          "gandfindsman",           "G-1A Starfighter",           "g1astarfighter",          "n", false, 5, 3, 1, 4, 4, 25, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::Elite, Upg::Crew, Upg::System, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Ruthless Freelancer",      "Ruthless Freelancer",    "ruthlessfreelancer",     "G-1A Starfighter",           "g1astarfighter",          "n", false, 3, 3, 1, 4, 4, 23, Act::Focus|Act::TargetLock|Act::Evade,                 {MT,             Upg::Crew, Upg::System, Upg::Illicit} },

  { Faction::Scum,   BaseSize::Large, "Dengar",                   "Dengar",                 "dengar",                 "JumpMaster 5000",            "jumpmaster5000",          "p", true,  9, 2, 2, 5, 4, 33, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Torpedo, Upg::Torpedo, Upg::Crew, Upg::SalvagedAstromech, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Tel Trevura",              "Tel Rrevura",            "teltrevura",             "JumpMaster 5000",            "jumpmaster5000",          "p", true,  7, 2, 2, 5, 4, 30, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Torpedo, Upg::Torpedo, Upg::Crew, Upg::SalvagedAstromech, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Manaroo",                  "Manaroo",                "manaroo",                "JumpMaster 5000",            "jumpmaster5000",          "p", true,  4, 2, 2, 5, 4, 27, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Torpedo, Upg::Torpedo, Upg::Crew, Upg::SalvagedAstromech, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Contracted Scout",         "Contracted Scout",       "contractedscout",        "JumpMaster 5000",            "jumpmaster5000",          "p", false, 3, 2, 2, 5, 4, 25, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Torpedo, Upg::Torpedo, Upg::Crew, Upg::SalvagedAstromech, Upg::Illicit} },

  { Faction::Rebel,  BaseSize::Small, "Poe Dameron",              "Poe Dameron",            "poedameron",             "T-70 X-Wing Fighter",        "t70xwing",                "x", true,  8, 3, 2, 3, 3, 31, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech, Upg::Tech} },
  { Faction::Rebel,  BaseSize::Small, "\"Blue Ace\"",             "Blue Ace",               "blueace",                "T-70 X-Wing Fighter",        "t70xwing",                "x", true,  5, 3, 2, 3, 3, 27, Act::Focus|Act::TargetLock|Act::Boost,                 {MT,             Upg::Torpedo, Upg::Astromech, Upg::Tech} },
  { Faction::Rebel,  BaseSize::Small, "Red Squadron Veteran",     "Red Sq. Veteran",        "redsquadronveteran",     "T-70 X-Wing Fighter",        "t70xwing",                "x", false, 4, 3, 2, 3, 3, 26, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech, Upg::Tech} },
  { Faction::Rebel,  BaseSize::Small, "Blue Squadron Novice",     "Blue Sq. Novice",        "bluesquadronnovice",     "T-70 X-Wing Fighter",        "t70xwing",                "x", false, 2, 3, 2, 3, 3, 24, Act::Focus|Act::TargetLock|Act::Boost,                 {MT,             Upg::Torpedo, Upg::Astromech, Upg::Tech} },
  { Faction::Rebel,  BaseSize::Small, "Ello Asty",                "Ello Asty",              "elloasty",               "T-70 X-Wing Fighter",        "t70xwing",                "x", true,  7, 3, 2, 3, 3, 30, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech, Upg::Tech} },
  { Faction::Rebel,  BaseSize::Small, "\"Red Ace\"",              "Red Ace",                "redace",                 "T-70 X-Wing Fighter",        "t70xwing",                "x", true,  6, 3, 2, 3, 3, 29, Act::Focus|Act::TargetLock|Act::Boost,                 {MT,             Upg::Torpedo, Upg::Astromech, Upg::Tech} },
  { Faction::Rebel,  BaseSize::Small, "Poe Dameron",              "Poe Dameron",            "poedameron-swx57",       "T-70 X-Wing Fighter",        "t70xwing",                "x", true,  9, 3, 2, 3, 3, 33, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech, Upg::Tech} },
  { Faction::Rebel,  BaseSize::Small, "Nien Nunb",                "Nien Nunb",              "niennunb",               "T-70 X-Wing Fighter",        "t70xwing",                "x", true,  7, 3, 2, 3, 3, 29, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech, Upg::Tech} },
  { Faction::Rebel,  BaseSize::Small, "\"Snap\" Wexley",          "Snap Wexley",            "snapwexley",             "T-70 X-Wing Fighter",        "t70xwing",                "x", true,  6, 3, 2, 3, 3, 28, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech, Upg::Tech} },
  { Faction::Rebel,  BaseSize::Small, "Jess Pava",                "Jess Pava",              "jesspava",               "T-70 X-Wing Fighter",        "t70xwing",                "x", true,  3, 3, 2, 3, 3, 25, Act::Focus|Act::TargetLock|Act::Boost,                 {MT,             Upg::Torpedo, Upg::Astromech, Upg::Tech} },

  { Faction::Empire, BaseSize::Small, "\"Omega Ace\"",            "Omega Ace",              "omegaace",               "TIE/fo Fighter",             "tiefofighter",            "O", true,  7, 2, 3, 3, 1, 20, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "\"Epsilon Leader\"",       "Epsilon Leader",         "epsilonleader",          "TIE/fo Fighter",             "tiefofighter",            "O", true,  6, 2, 3, 3, 1, 19, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,             Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "\"Zeta Ace",               "Zeta Ace",               "zetaace",                "TIE/fo Fighter",             "tiefofighter",            "O", true,  5, 2, 3, 3, 1, 18, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "Omega Squadron Pilot",     "Omega Sq. Pilot",        "omegasquadronpilot",     "TIE/fo Fighter",             "tiefofighter",            "O", false, 4, 2, 3, 3, 1, 17, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "Zeta Squadron Pilot",      "Zeta Sq. Pilot",         "zetasquadronpilot",      "TIE/fo Fighter",             "tiefofighter",            "O", false, 3, 2, 3, 3, 1, 16, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,             Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "Epsilon Squadron Pilot",   "Epsilon Sq. Pilot",      "epsilonsquadronpilot",   "TIE/fo Fighter",             "tiefofighter",            "O", false, 1, 2, 3, 3, 1, 15, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,             Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "\"Omega Leader",           "Omega Leader",           "omegaleader",            "TIE/fo Fighter",             "tiefofighter",            "O", true,  8, 2, 3, 3, 1, 21, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "\"Zeta Leader",            "Zeta Leader",            "zetaleader",             "TIE/fo Fighter",             "tiefofighter",            "O", true,  7, 2, 3, 3, 1, 20, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "\"Epsilon Ace",            "Epsilon Ace",            "epsilonace",             "TIE/fo Fighter",             "tiefofighter",            "O", true,  4, 2, 3, 3, 1, 17, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,             Upg::Tech} },

  { Faction::Rebel,  BaseSize::Small, "Norra Wexley",             "Norra Wexley",           "norrawexley",            "ARC-170",                    "arc170",                  "c", true,  7, 2, 1, 6, 3, 29, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Torpedo, Upg::Crew, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Shara Bey",                "Shara Bey",              "sharabey",               "ARC-170",                    "arc170",                  "c", true,  6, 2, 1, 6, 3, 28, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Torpedo, Upg::Crew, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Thane Kyrell",             "Thane Kyrell",           "thanekyrell",            "ARC-170",                    "arc170",                  "c", true,  4, 2, 1, 6, 3, 26, Act::Focus|Act::TargetLock,                            {MT,             Upg::Torpedo, Upg::Crew, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Braylen Stramm",           "Braylen Stramm",         "braylenstramm",          "ARC-170",                    "arc170",                  "c", true,  3, 2, 1, 6, 3, 25, Act::Focus|Act::TargetLock,                            {MT,             Upg::Torpedo, Upg::Crew, Upg::Astromech} },

  { Faction::Empire, BaseSize::Small, "\"Quickdraw\"",            "Quickdraw",              "quickdraw",              "TIE/sf Fighter",             "tiesffighter",            "S", true,  9, 2, 2, 3, 3, 29, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::System, Upg::Missile, Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "\"Backdraft\"",            "Backdraft",              "backdraft",              "TIE/sf Fighter",             "tiesffighter",            "S", true,  7, 2, 2, 3, 3, 27, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::System, Upg::Missile, Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "Omega Specialist",         "Omega Specialist",       "omegaspecialist",        "TIE/sf Fighter",             "tiesffighter",            "S", false, 5, 2, 2, 3, 3, 25, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::System, Upg::Missile, Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "Zeta Specialist",          "Zeta Specialist",        "zetaspecialist",         "TIE/sf Fighter",             "tiesffighter",            "S", false, 3, 2, 2, 3, 3, 23, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT,             Upg::System, Upg::Missile, Upg::Tech} },

  { Faction::Scum,   BaseSize::Small, "Fenn Rau",                 "Fenn Rau",               "fennrau",                "Protectorate Starfighter",   "protectoratestarfighter", "M", true,  9, 3, 3, 4, 0, 28, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Torpedo} },
  { Faction::Scum,   BaseSize::Small, "Old Teroch",               "Old Teroch",             "oldteroch",              "Protectorate Starfighter",   "protectoratestarfighter", "M", true,  7, 3, 3, 4, 0, 26, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Torpedo} },
  { Faction::Scum,   BaseSize::Small, "Kad Solus",                "Kad Solus",              "kadsolus",               "Protectorate Starfighter",   "protectoratestarfighter", "M", true,  6, 3, 3, 4, 0, 25, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Torpedo} },
  { Faction::Scum,   BaseSize::Small, "Concord Dawn Ace",         "Concord Dawn Ace",       "concorddawnace",         "Protectorate Starfighter",   "protectoratestarfighter", "M", false, 5, 3, 3, 4, 0, 23, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Torpedo} },
  { Faction::Scum,   BaseSize::Small, "Concord Dawn Veteran",     "Concord Dawn Vet.",      "concorddawnveteran",     "Protectorate Starfighter",   "protectoratestarfighter", "M", false, 3, 3, 3, 4, 0, 22, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Torpedo} },
  { Faction::Scum,   BaseSize::Small, "Zealous Recruit",          "Zealous Recruit",        "zealousrecruit",         "Protectorate Starfighter",   "protectoratestarfighter", "M", false, 1, 3, 3, 4, 0, 20, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT,             Upg::Torpedo} },

  { Faction::Scum,   BaseSize::Large, "Ketsu Onyo",               "Ketsy Onyo",             "ketsuonyo",              "Lancer-class Pursuit Craft", "lancerclasspursuitcraft", "L", true,  7, 3, 2, 7, 3, 38, Act::Focus|Act::TargetLock|Act::Evade|Act::RotateArc,  {MT, Upg::Elite, Upg::Crew, Upg::Illicit, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Asajj Ventress",           "Asajj Ventress",         "asajjventress",          "Lancer-class Pursuit Craft", "lancerclasspursuitcraft", "L", true,  6, 3, 2, 7, 3, 37, Act::Focus|Act::TargetLock|Act::Evade|Act::RotateArc,  {MT, Upg::Elite, Upg::Crew, Upg::Illicit, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Sabine Wren",              "Sabine Wren",            "sabinewren",             "Lancer-class Pursuit Craft", "lancerclasspursuitcraft", "L", true,  5, 3, 2, 7, 3, 35, Act::Focus|Act::TargetLock|Act::Evade|Act::RotateArc,  {MT,             Upg::Crew, Upg::Illicit, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Shadowport Hunter",        "Shadowport Hunter",      "shadowporthunter",       "Lancer-class Pursuit Craft", "lancerclasspursuitcraft", "L", false, 2, 3, 2, 7, 3, 33, Act::Focus|Act::TargetLock|Act::Evade|Act::RotateArc,  {MT,             Upg::Crew, Upg::Illicit, Upg::Illicit} },

  { Faction::Rebel,  BaseSize::Large, "Cassian Andor",            "Cassian Andor",          "cassianandor",           "U-Wing",                     "uwing",                   "u", true,  6, 3, 1, 4, 4, 27, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::System, Upg::Torpedo, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Bodhi Rook",               "Bodhi Rook",             "bodhirook",              "U-Wing",                     "uwing",                   "u", true,  4, 3, 1, 4, 4, 25, Act::Focus|Act::TargetLock,                            {MT,             Upg::System, Upg::Torpedo, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Heff Tobber",              "Heff Tobber",            "hefftobber",             "U-Wing",                     "uwing",                   "u", true,  3, 3, 1, 4, 4, 24, Act::Focus|Act::TargetLock,                            {MT,             Upg::System, Upg::Torpedo, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Blue Squadron Pathfinder", "Blue Sq. Pathfinder",    "bluesquadronpathfinder", "U-Wing",                     "uwing",                   "u", false, 2, 3, 1, 4, 4, 23, Act::Focus|Act::TargetLock,                            {MT,             Upg::System, Upg::Torpedo, Upg::Crew, Upg::Crew} },

  { Faction::Empire, BaseSize::Small, "\"Duchess\"",              "Duchess",                "duchess",                "TIE Striker",                "tiestriker",              "T", true,  8, 3, 2, 4, 0, 23, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "\"Pure Sebacc\"",          "Pure Sebacc",            "puresebacc",             "TIE Striker",                "tiestriker",              "T", true,  6, 3, 2, 4, 0, 22, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "\"Countdown\"",            "Countdown",              "countdown",              "TIE Striker",                "tiestriker",              "T", true,  5, 3, 2, 4, 0, 20, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT,           } },
  { Faction::Empire, BaseSize::Small, "Black Squadron Scout",     "Black Sq. Pilot",        "blacksquadronpilot",     "TIE Striker",                "tiestriker",              "T", true,  4, 3, 2, 4, 0, 20, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "Scarif Defender",          "Scarif Defender",        "scarifdefender",         "TIE Striker",                "tiestriker",              "T", true,  3, 3, 2, 4, 0, 18, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT,           } },
  { Faction::Empire, BaseSize::Small, "Imperial Trainee",         "Imperial Trainee",       "imperialtrainss",        "TIE Striker",                "tiestriker",              "T", true,  1, 3, 2, 4, 0, 17, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT,           } },
  */
};
