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
const Bearing LS = Bearing::LSloop;
const Bearing RS = Bearing::RSloop;
const Bearing LR = Bearing::LTroll;
const Bearing RR = Bearing::RTroll;

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
            {3,LT,W}, {3,LB,W}, {3,ST,W}, {3,RB,W}, {3,RT,W}, {3,KT,R},
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

M mHWK29 = {                    {4,ST,R},
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

M mM3AIN = {                                                  {5,KT,R},
                                {4,ST,W},
                      {3,LB,W}, {3,ST,G}, {3,RB,W},           {3,KT,R},
            {2,LT,W}, {2,LB,G}, {2,ST,G}, {2,RB,G}, {2,RT,W},
            {1,LT,W}, {1,LB,G},           {1,RB,G}, {1,RT,W}
};

M mSTARV = {                    {4,ST,W},
                      {3,LB,W}, {3,ST,G}, {3,RB,W},           {3,LS,R}, {3,RS,R},
            {2,LT,W}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,W},
            {1,LT,W}, {1,LB,G}, {1,ST,G}, {1,RB,G}, {1,RT,W}
};

M mAGGRE = {                                                  {4,KT,R},
                      {3,LB,G}, {3,ST,G}, {3,RB,G},                     {3,LS,R}, {3,RS,R},
            {2,LT,W}, {2,LB,G}, {2,ST,G}, {2,RB,G}, {2,RT,W},
            {1,LT,W}, {1,LB,G}, {1,ST,G}, {1,RB,G}, {1,RT,W}
};

M mYV666 = {                    {4,ST,W},
            {3,LT,W}, {3,LB,W}, {3,ST,G}, {3,RB,W}, {3,RT,W},
            {2,LT,R}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,R},
                      {1,LB,G}, {1,ST,G}, {1,RB,G},
                                {0,SY,R}
};

M mKIHRA = {                                                  {5,KT,R},
                                {4,ST,W},                     {4,KT,R},
                      {3,LB,W}, {3,ST,W}, {3,RB,W},
            {2,LT,W}, {2,LB,G}, {2,ST,G}, {2,RB,G}, {2,RT,W},
            {1,LT,W}, {1,LB,G},           {1,RB,G}, {1,RT,W}
};

M mKWING = {          {3,LB,W}, {3,ST,W}, {3,RB,W},
            {2,LT,W}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,W},
                      {1,LB,G}, {1,ST,G}, {1,RB,G}
};

M mTIEPU = {                                                  {4,KT,R},
            {3,LT,W}, {3,LB,W}, {3,ST,W}, {3,RB,W}, {3,RT,W},
            {2,LT,R}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,R},
                      {1,LB,G}, {1,ST,G}, {1,RB,G}
};

M mVCX10 = {                                                  {5,KT,R},
                                {4,ST,W},
            {3,LT,R}, {3,LB,W}, {3,ST,W}, {3,RB,W}, {3,RT,R},
            {2,LT,W}, {2,LB,G}, {2,ST,G}, {2,RB,G}, {2,RT,W},
            {1,LT,R}, {1,LB,W}, {1,ST,G}, {1,RB,W}, {1,RT,R}
};

M mATTAC = {                    {4,ST,W},                     {4,KT,R},
            {3,LT,R}, {3,LB,W}, {3,ST,W}, {3,RB,W}, {3,RT,R},
            {2,LT,W}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,W},
            {1,LT,R}, {1,LB,G}, {1,ST,G}, {1,RB,G}, {1,RT,R}
};

M mTIEAP = {                    {5,ST,W},
                                {4,ST,G},                     {4,KT,R},
            {3,LT,W}, {3,LB,W}, {3,ST,G}, {3,RB,W}, {3,RT,W},
            {2,LT,W}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,W},
            {1,LT,G}, {1,LB,G},           {1,RB,G}, {1,RT,G}
};

M mG1AST = {                    {4,ST,W},                     {4,KT,R},
                      {3,LB,R}, {3,ST,G}, {3,RB,R},           {3,KT,R},
            {2,LT,W}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,W},
            {1,LT,R}, {1,LB,G}, {1,ST,G}, {1,RB,G}, {1,RT,R}
};

M mJUMPM = {                    {4,ST,W},                     {4,KT,R},
                      {3,LB,W}, {3,ST,W}, {3,RB,W},
            {2,LT,G}, {2,LB,G}, {2,ST,G}, {2,RB,W}, {2,RT,W},           {2,LS,W}, {2,RS,R},
            {1,LT,G}, {1,LB,G}, {1,ST,G}, {1,RB,W}, {1,RT,W}
};

M mT70XW = {                    {4,ST,W},                     {4,KT,R},
            {3,LT,W}, {3,LB,W}, {3,ST,G}, {3,RB,W}, {3,RT,W},           {3,LR,R}, {3,RR,R},
            {2,LT,W}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,W},
                      {1,LB,G}, {1,ST,G}, {1,RB,G}
};

M mTIEFO = {                    {5,ST,W},
                                {4,ST,W},                     {4,KT,R},
            {3,LT,W}, {3,LB,W}, {3,ST,G}, {3,RB,W}, {3,RT,W},
            {2,LT,G}, {2,LB,G}, {2,ST,G}, {2,RB,G}, {2,RT,G},           {2,LS,R}, {2,RS,R},
            {1,LT,W},                               {1,RT,W}
};

M mARC17 = {                    {4,ST,R},                     {4,KT,R},
            {3,LT,R}, {3,LB,W}, {3,ST,W}, {3,RB,W}, {3,RT,R},
            {2,LT,W}, {2,LB,G}, {2,ST,G}, {2,RB,G}, {2,RT,W},
                      {1,LB,G}, {1,ST,G}, {1,RB,G}
};

M mTIESF = {                    {4,ST,W},
            {3,LT,R}, {3,LB,W}, {3,ST,G}, {3,RB,W}, {3,RT,R}, {3,LS,R}, {3,RS,R},
            {2,LT,W}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,W},
            {1,LT,R}, {1,LB,G}, {1,ST,G}, {1,RB,G}, {1,RT,R}
};

M mPROTE = {                    {5,ST,W},
                                {4,ST,W},                     {4,KT,R},
            {3,LT,W}, {3,LB,W}, {3,ST,G}, {3,RB,W}, {3,RT,W},
            {2,LT,G}, {2,LB,G}, {2,ST,G}, {2,RB,G}, {2,RT,G},           {2,LR,R}, {2,RR,R},
            {1,LT,W},                               {1,RT,W}
};

M mLANCE = {                    {5,ST,W},                     {5,KT,R},
                                {4,ST,G},
            {3,LT,G}, {3,LB,G}, {3,ST,G}, {3,RB,G}, {3,RT,G},
            {2,LT,W}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,W},
                      {1,LB,W}, {1,ST,W}, {1,RB,W}
};

M mUWING = {                    {4,ST,W},
                      {3,LB,W}, {3,ST,W}, {3,RB,W},
            {2,LT,W}, {2,LB,G}, {2,ST,G}, {2,RB,G}, {2,RT,W},
                      {1,LB,G}, {1,ST,G}, {1,RB,G},
                                {0,SY,R}
};

M mTIEST = {          {3,LB,W}, {3,ST,G}, {3,RB,W},
            {2,LT,W}, {2,LB,W}, {2,ST,G}, {2,RB,W}, {2,RT,W}, {2,KT,R}, {2,LS,R}, {2,RS,R},
            {1,LT,W}, {1,LB,G}, {1,ST,G}, {1,RB,G}, {1,RT,W}
};



#define MT  Upg::Modification,Upg::Title

std::list<Pilot> Pilot::pilots = {
  // faction         base size         name                        short                    xws                       ship                          xws                        gly  maneuv unique ps at ag hu sh cst  actions                                                 upgrades
  { Faction::Rebel,  BaseSize::Small, "Luke Skywalker",           "Luke",                  "lukeskywalker",          "X-Wing",                     "xwing",                    "w", mXWING, true,  8, 3, 2, 3, 2, 28, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech}, true,  "When defending, you may change 1 of your {FOCUS} results to a {EVADE} result." },
  { Faction::Rebel,  BaseSize::Small, "Biggs Darklighter",        "Biggs",                 "biggsdarklighter",       "X-Wing",                     "xwing",                    "w", mXWING, true,  5, 3, 2, 3, 2, 25, Act::Focus|Act::TargetLock,                            {MT,             Upg::Torpedo, Upg::Astromech}, true,  "Other friendly ships at Range 1 cannot be targeted by attacks if the attacker could target your instead." },
  { Faction::Rebel,  BaseSize::Small, "Red Squadron Pilot",       "Red Sq. Pilot",         "redsquadronpilot",       "X-Wing",                     "xwing",                    "w", mXWING, false, 4, 3, 2, 3, 2, 23, Act::Focus|Act::TargetLock,                            {MT,             Upg::Torpedo, Upg::Astromech}, false, "Created as an elite starfighter squad, Red Squadron included some of the best pilots in the Rebel Alliance." },
  { Faction::Rebel,  BaseSize::Small, "Rookie Pilot",             "Rookie Pilot",          "rookiepilot",            "X-Wing",                     "xwing",                    "w", mXWING, false, 2, 3, 2, 3, 2, 21, Act::Focus|Act::TargetLock,                            {MT,             Upg::Torpedo, Upg::Astromech}, false, "Designed by Incom Corporation, the T-65 X-wing quickly proved to be one of the most effective military vehicles in the galaxy and a boon to the Rebellion." },
  { Faction::Rebel,  BaseSize::Small, "Wedge Antilles",           "Wedge",                 "wedgeantilles",          "X-Wing",                     "xwing",                    "w", mXWING, true,  9, 3, 2, 3, 2, 29, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech}, true,  "When attacking, reduce the defender's agility value by 1 (to a minimum of 0)." },
  { Faction::Rebel,  BaseSize::Small, "Garven Dreis",             "Garven",                "garvendreis",            "X-Wing",                     "xwing",                    "w", mXWING, true,  6, 3, 2, 3, 2, 26, Act::Focus|Act::TargetLock,                            {MT,             Upg::Torpedo, Upg::Astromech}, true,  "After spending a focus token, you may place that token on any other friendly ship at Range 1-2 (instad of discarding it)." },
  { Faction::Rebel,  BaseSize::Small, "\"Hobbie\" Klivian",       "Hobbie",                "hobbieklivian",          "X-Wing",                     "xwing",                    "w", mXWING, true,  5, 3, 2, 3, 2, 25, Act::Focus|Act::TargetLock,                            {MT,             Upg::Torpedo, Upg::Astromech}, true,  "When you acquire or spend a target lock, you may remove 1 stress token from your ship." },
  { Faction::Rebel,  BaseSize::Small, "Jek Porkins",              "Porkins",               "jekporkins",             "X-Wing",                     "xwing",                    "w", mXWING, true,  7, 3, 2, 3, 2, 26, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech}, true,  "When you receive a stress token, you may remove it and roll 1 attack die.  On a {HIT} result, deal 1 facedown Damage card to this ship." },
  { Faction::Rebel,  BaseSize::Small, "Tarn Mison",               "Tarn Mison",            "tarnmison",              "X-Wing",                     "xwing",                    "w", mXWING, true,  3, 3, 2, 3, 2, 23, Act::Focus|Act::TargetLock,                            {MT,             Upg::Torpedo, Upg::Astromech}, true,  "When an enemy ship declares you as the target of an attack you may acquire a target lock on that ship." },
  { Faction::Rebel,  BaseSize::Small, "Wes Janson",               "Wes Janson",            "wasjanson",              "X-Wing",                     "xwing",                    "w", mXWING, true,  8, 3, 2, 3, 2, 29, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech}, true,  "After you perform an attack, you may remove 1 focus, evade, or blue target lock token from the defender." },

  { Faction::Empire, BaseSize::Small, "\"Mauler Mithel\"",        "Mauler Mithel",         "maulermithel",           "TIE Fighter",                "tiefighter",               "F", mTIEFI, true,  7, 2, 3, 3, 0, 17, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite}, true,  "When attacking at Range 1, roll 1 additional attack die." },
  { Faction::Empire, BaseSize::Small, "\"Dark Curse\"",           "Dark Curse",            "darkcurse",              "TIE Fighter",                "tiefighter",               "F", mTIEFI, true,  6, 2, 3, 3, 0, 16, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT,           }, true,  "When defending, ships attacking you cannot spend focus tokens or reroll attack dice." },
  { Faction::Empire, BaseSize::Small, "\"Night Beast\"",          "Night Beast",           "nightbeast",             "TIE Fighter",                "tiefighter",               "F", mTIEFI, true,  5, 2, 3, 3, 0, 15, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT,           }, true,  "After executing a green maneuver, you may perform a free focus action." },
  { Faction::Empire, BaseSize::Small, "Black Squadron Pilot",     "Black Sq. Plt",         "blacksquadronpilot",     "TIE Fighter",                "tiefighter",               "F", mTIEFI, false, 4, 2, 3, 3, 0, 14, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite}, false, "The TIE fighter has no shields or life support systems, forcing TIE pilots to depend solely on their skills to survive." },
  { Faction::Empire, BaseSize::Small, "Obsidian Squadron Pilot",  "Obsidian Sq. Plt",      "obsidiansquadronpilot",  "TIE Fighter",                "tiefighter",               "F", mTIEFI, false, 3, 2, 3, 3, 0, 13, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT,           }, false, "The TIE fighter's Twin Ion Engine system was designed for speed, making the TIE one of the most maneuverable starships ever produced." },
  { Faction::Empire, BaseSize::Small, "Academy Pilot",            "Academy Plt",           "academypilot",           "TIE Fighter",                "tiefighter",               "F", mTIEFI, false, 1, 2, 3, 3, 0, 12, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT,           }, false, "Developed by Sienar Fleet Systems, the Empire used the fast and agile TIE/ln as its primary starfighter throughout most of the Galactic Civil War." },
  { Faction::Empire, BaseSize::Small, "\"Howlrunner\"",           "Howlrunner",            "howlrunner",             "TIE Fighter",                "tiefighter",               "F", mTIEFI, true,  8, 2, 3, 3, 0, 18, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite}, true,  "When another friendly ship at Range 1 is attacking with its primary weapon, it may reroll 1 attack die." },
  { Faction::Empire, BaseSize::Small, "\"Backstabber\"",          "Backstabber",           "backstabber",            "TIE Fighter",                "tiefighter",               "F", mTIEFI, true,  6, 2, 3, 3, 0, 16, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT,           }, true,  "When attacking from outside the defender's firing arc, roll 1 additional attack die." },
  { Faction::Empire, BaseSize::Small, "\"Winged Gundark\"",       "Winged Gundark",        "wingedgundark",          "TIE Fighter",                "tiefighter",               "F", mTIEFI, true,  5, 2, 3, 3, 0, 15, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT,           }, true,  "When attacking at Range 1, you may change 1 of your {HIT} results to a {CRIT} result." },
  { Faction::Empire, BaseSize::Small, "\"Scourge\"",              "Scourge",               "scourge",                "TIE Fighter",                "tiefighter",               "F", mTIEFI, true,  7, 2, 3, 3, 0, 17, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite}, true,  "When attacking a defender that has 1 or more Damage cards, roll 1 additional attack die." },
  { Faction::Empire, BaseSize::Small, "\"Wampa\"",                "Wampa",                 "wampa",                  "TIE Fighter",                "tiefighter",               "F", mTIEFI, true,  4, 2, 3, 3, 0, 14, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT,           }, true,  "When attacking, you may cancel all dice results.  If you cancel a {CRIT} result, deal 1 facedown Damage card to the defender." },
  { Faction::Empire, BaseSize::Small, "\"Youngster\"",            "Youngster",             "youngster",              "TIE Fighter",                "tiefighter",               "F", mTIEFI, true,  6, 2, 3, 3, 0, 15, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite}, true,  "Friendly TIE fighters at Range 1-3 may perform the action on your equipped {ELITE} Upgrade card." },
  { Faction::Empire, BaseSize::Small, "\"Chaser\"",               "Chaser",                "chaser",                 "TIE Fighter",                "tiefighter",               "F", mTIEFI, true,  3, 2, 3, 3, 0, 14, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT,           }, true,  "When another friendly ship at Range 1 spends a focus token, assign a focus token to your ship." },

  { Faction::Rebel,  BaseSize::Small, "Horton Salm",              "Horton Salm",           "hortonsalm",             "Y-Wing",                     "ywing",                    "y", mYWING, true,  8, 2, 1, 5, 3, 25, Act::Focus|Act::TargetLock,                            {MT, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Astromech}, true,  "When attacking at Range 2-3, you may reroll any of your blank results." },
  { Faction::Rebel,  BaseSize::Small, "\"Dutch\" Vander",         "Dutch Vander",          "dutchvander",            "Y-Wing",                     "ywing",                    "y", mYWING, true,  6, 2, 1, 5, 3, 23, Act::Focus|Act::TargetLock,                            {MT, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Astromech}, true,  "After acquiring a target lock, choose another friendly ship at Range 1-2.  The chosen ship may immediately acquire a target lock." },
  { Faction::Rebel,  BaseSize::Small, "Gray Squadron Pilot",      "Gray Sq. Plt",          "graysquadronpilot",      "Y-Wing",                     "ywing",                    "y", mYWING, false, 4, 2, 1, 5, 3, 20, Act::Focus|Act::TargetLock,                            {MT, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Astromech}, false, "Long after the Y-wing was to be phased out, its speed, durability, and weapon options helped it remain a staple in the Rebel fleet" },
  { Faction::Rebel,  BaseSize::Small, "Gold Squadron Pilot",      "Gold Sq. Plt",          "goldsquadronpilot",      "Y-Wing",                     "ywing",                    "y", mYWING, false, 2, 2, 1, 5, 3, 18, Act::Focus|Act::TargetLock,                            {MT, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Astromech}, false, "The versatile and reliable BTL-A4 Y-wing was the Rebellion's primary starfighter until the arrival of the T-65 X-wing." },

  { Faction::Empire, BaseSize::Small, "Darth Vader",              "Darth Vader",           "darthvader",             "TIE Advanced",               "tieadvanced",              "A", mTIEAD, true,  9, 2, 3, 3, 2, 29, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Missile}, true,  "During your \"Perform Action\" step, you may perform 2 actions." },
  { Faction::Empire, BaseSize::Small, "Maarek Stele",             "Maarek Steele",         "maarekstele",            "TIE Advanced",               "tieadvanced",              "A", mTIEAD, true,  7, 2, 3, 3, 2, 27, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Missile}, true,  "When your attack deals a faceup Damage card to the defender, instead draw 3 Damage cards, choose 1 to deal, and discard the others." },
  { Faction::Empire, BaseSize::Small, "Storm Squadron Pilot",     "Storm Sq. Plt",         "stormsquadronpilot",     "TIE Advanced",               "tieadvanced",              "A", mTIEAD, false, 4, 2, 3, 3, 2, 23, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,             Upg::Missile}, false, "The TIE Advanced improved on the popular TIE/ln design by adding shielding, better weapons systems, curved solar panels, and a hyperdrive." },
  { Faction::Empire, BaseSize::Small, "Tempest Squadron Pilot",   "Tempest Sq. Plt",       "tempestsquadronpilot",   "TIE Advanced",               "tieadvanced",              "A", mTIEAD, false, 2, 2, 3, 3, 2, 21, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,             Upg::Missile}, false, "The TIE Advanced was produced in limited quantities, but later Sienar engineers incorporated many of its best qualities into their next TIE model: the TIE Interceptor." },
  { Faction::Empire, BaseSize::Small, "Zertik Strom",             "Zertik Strom",          "zertikstrom",            "TIE Advanced",               "tieadvanced",              "A", mTIEAD, true,  6, 2, 3, 3, 2, 26, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Missile}, true,  "Enemy ships at Range 1 cannot add their range combat bonus when attacking." },
  { Faction::Empire, BaseSize::Small, "Juno Eclipse",             "Juno Eclipse",          "junoeclipse",            "TIE Advanced",               "tieadvanced",              "A", mTIEAD, true,  8, 2, 3, 3, 2, 28, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Missile}, true,  "When you reveal your maneuver, you may increase or decrease its speed by 1 (to a minimum of 1)." },
  { Faction::Empire, BaseSize::Small, "Commander Alozen",         "Cmdr. Alozen",          "commanderalozen",        "TIE Advanced",               "tieadvanced",              "A", mTIEAD, true,  5, 2, 3, 3, 2, 25, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Missile}, true,  "At the start of the Combat phase, you may acquire a target lock on an enemy ship at Range 1." },
  { Faction::Empire, BaseSize::Small, "Lieutenant Colzet",        "Lt. Colzet",            "lieutenantcolzet",       "TIE Advanced",               "tieadvanced",              "A", mTIEAD, true,  3, 2, 3, 3, 2, 23, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,             Upg::Missile}, true,  "At the start of the End phase, you may spend a target lock you have on an enemy ship to flip 1 random facedown Damage card assigned to it faceup." },

  { Faction::Rebel,  BaseSize::Large, "Han Solo",                 "Han Solo",              "hansolo",                "YT-1300",                    "yt1300",                   "m", mYT130, true,  9, 3, 1, 8, 5, 46, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Crew, Upg::Crew}, true,  "When attacking, you may reroll all of your dice.  If you choose to do so, you must reroll as many of your dice sa possible." },
  { Faction::Rebel,  BaseSize::Large, "Lando Calrissian",         "Lando",                 "landocalrissian",        "YT-1300",                    "yt1300",                   "m", mYT130, true,  7, 3, 1, 8, 5, 44, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Crew, Upg::Crew}, true,  "After you execute a green maneuver, choose 1 other friendly ship at Range 1.  That ship may perform 1 free action shown in its action bar." },
  { Faction::Rebel,  BaseSize::Large, "Chewbacca",                "Chewbacca",             "chewbacca",              "YT-1300",                    "yt1300",                   "m", mYT130, true,  5, 3, 1, 8, 5, 42, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Crew, Upg::Crew}, true,  "When you are dealt a faceup Damage card, immediately flip it facedown (without resolving its ability)." },
  { Faction::Rebel,  BaseSize::Large, "Outer Rim Smuggler",       "Outer Rim Smug",        "outerrimsmuggler",       "YT-1300",                    "yt1300",                   "m", mYT130, false, 1, 2, 1, 6, 4, 27, Act::Focus|Act::TargetLock,                            {MT,             Upg::Missile, Upg::Crew, Upg::Crew}, false, "Known for its durability and modular design, the YT-1300 is one of the most popular, widely used freighters in the galaxy." },
  { Faction::Rebel,  BaseSize::Large, "Han Solo",                 "Han Solo",              "hansolo-swx57",          "YT-1300",                    "yt1300",                   "m", mYT130, true,  9, 3, 1, 8, 5, 46, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Crew, Upg::Crew}, true,  "When you are placed during setup, you can be placed anywhere in the play area beyond Range 3 of enemy ships." },
  { Faction::Rebel,  BaseSize::Large, "Rey",                      "Rey",                   "rey",                    "YT-1300",                    "yt1300",                   "m", mYT130, true,  8, 3, 1, 8, 5, 45, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Crew, Upg::Crew}, true,  "When attacking or defending, if the enemy ship is inside your firing arc, you may reroll up to 2 of your blank results." },
  { Faction::Rebel,  BaseSize::Large, "Chewbacca",                "Chewbacca",             "chewbacca-swx57",        "YT-1300",                    "yt1300",                   "m", mYT130, true,  5, 3, 1, 8, 5, 42, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Crew, Upg::Crew}, true,  "After another friendly ship at Range 1-3 is destroyed (but has not fled the battlefield, you may perform an attack." },
  { Faction::Rebel,  BaseSize::Large, "Resistance Sympathizer",   "Res Sympathizer",       "resistancesympathizer",  "YT-1300",                    "yt1300",                   "m", mYT130, false, 3, 3, 1, 8, 5, 38, Act::Focus|Act::TargetLock,                            {MT,             Upg::Missile, Upg::Crew, Upg::Crew}, false, "After the destruction of the Hosnian system, some spacers willingly aided the Resistance against the malevolent First Order." },

  { Faction::Empire, BaseSize::Large, "Boba Fett",                "Boba Fett",             "bobafett",               "Firespray-31",               "firespray31",              "f", mFSP31, true,  8, 3, 2, 6, 4, 39, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::Elite, Upg::Cannon, Upg::Bomb, Upg::Crew, Upg::Missile}, true,  "When you reveal a bank maneuver ({LBANK} or {RBANK}), you may rotate your dial to the other bank maneuver of the same speed." },
  { Faction::Empire, BaseSize::Large, "Kath Scarlet",             "Kath Scarlet",          "kathscarlet",            "Firespray-31",               "firespray31",              "f", mFSP31, true,  7, 3, 2, 6, 4, 38, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::Elite, Upg::Cannon, Upg::Bomb, Upg::Crew, Upg::Missile}, true,  "When attacking, the defender receives 1 stress token if he cancels at least 1 {CRIT} result." },
  { Faction::Empire, BaseSize::Large, "Krassis Trelix",           "Krasses Trelix",        "krassistrelix",          "Firespray-31",               "firespray31",              "f", mFSP31, true,  5, 3, 2, 6, 4, 36, Act::Focus|Act::TargetLock|Act::Evade,                 {MT,             Upg::Cannon, Upg::Bomb, Upg::Crew, Upg::Missile}, true,  "When attacking with a secondary weapon, you may reroll 1 attack die." },
  { Faction::Empire, BaseSize::Large, "Bounty Hunter",            "Bounty Hunter",         "bountyhunter",           "Firespray-31",               "firespray31",              "f", mFSP31, false, 3, 3, 2, 6, 4, 33, Act::Focus|Act::TargetLock|Act::Evade,                 {MT,             Upg::Cannon, Upg::Bomb, Upg::Crew, Upg::Missile}, false, "Originally intended as a prisoner transport, the Firespray patrol craft features a versatile weapons array and heavy armor plating." },

  { Faction::Rebel,  BaseSize::Small, "Tycho Celchu",             "Tycho Celchu",          "tychocelchu",            "A-Wing",                     "awing",                    "a", mAWING, true,  8, 2, 3, 2, 2, 26, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT, Upg::Elite, Upg::Missile} },
  { Faction::Rebel,  BaseSize::Small, "Arvel Crynyd",             "Arvel Crynyd",          "arvelcrynyd",            "A-Wing",                     "awing",                    "a", mAWING, true,  6, 2, 3, 2, 2, 23, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT,             Upg::Missile} },
  { Faction::Rebel,  BaseSize::Small, "Green Squadron Pilot",     "Green Sq. Pilot",       "greensquadronpilot",     "A-Wing",                     "awing",                    "a", mAWING, false, 3, 2, 3, 2, 2, 19, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT, Upg::Elite, Upg::Missile} },
  { Faction::Rebel,  BaseSize::Small, "Prototype Pilot",          "Prototype Pilot",       "prototypepilot",         "A-Wing",                     "awing",                    "a", mAWING, false, 1, 2, 3, 2, 2, 17, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT,             Upg::Missile} },
  { Faction::Rebel,  BaseSize::Small, "Jake Farrell",             "Jake Farrell",          "jakefarrell",            "A-Wing",                     "awing",                    "a", mAWING, true , 7, 2, 3, 2, 2, 24, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT, Upg::Elite, Upg::Missile} },
  { Faction::Rebel,  BaseSize::Small, "Gemmer Sojan",             "Gemmer Sojan",          "gennersojan",            "A-Wing",                     "awing",                    "a", mAWING, true , 5, 2, 3, 2, 2, 22, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT,             Upg::Missile} },

  { Faction::Empire, BaseSize::Small, "Soontir Fel",              "Soontir Fel",           "soontirfel",             "TIE Interceptor",            "tieinterceptor",           "I", mTIEIN, true,  9, 3, 3, 3, 0, 27, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "Turr Phennir",             "Turr Phennir",          "turrphennir",            "TIE Interceptor",            "tieinterceptor",           "I", mTIEIN, true,  7, 3, 3, 3, 0, 25, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "\"Fel's Wrath\"",          "Fel's Wrath",           "felswrath",              "TIE Interceptor",            "tieinterceptor",           "I", mTIEIN, true,  5, 3, 3, 3, 0, 23, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT,           } },
  { Faction::Empire, BaseSize::Small, "Saber Squadron Pilot",     "Saber Sq. Pilot",       "sabersquadronpilot",     "TIE Interceptor",            "tieinterceptor",           "I", mTIEIN, false, 4, 3, 3, 3, 0, 21, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "Avenger Squadron Pilot",   "Avenger Sq. Pilot",     "avengersquadronpilot",   "TIE Interceptor",            "tieinterceptor",           "I", mTIEIN, false, 3, 3, 3, 3, 0, 20, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT,           } },
  { Faction::Empire, BaseSize::Small, "Alpha Squadron Pilot",     "Alpha Sq. Pilot",       "alphasquadronpilot",     "TIE Interceptor",            "tieinterceptor",           "I", mTIEIN, false, 1, 3, 3, 3, 0, 18, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT,           } },
  { Faction::Empire, BaseSize::Small, "Carnor Jax",               "Carnor Jax",            "carnorjax",              "TIE Interceptor",            "tieinterceptor",           "I", mTIEIN, true,  8, 3, 3, 3, 0, 26, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "Tetran Cowall",            "Tetran Cowall",         "tetrancowell",           "TIE Interceptor",            "tieinterceptor",           "I", mTIEIN, true,  7, 3, 3, 3, 0, 24, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "Kir Kanos",                "Kir Kanos",             "kirkanos",               "TIE Interceptor",            "tieinterceptor",           "I", mTIEIN, true,  6, 3, 3, 3, 0, 24, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT,           } },
  { Faction::Empire, BaseSize::Small, "Lieutenant Lorrir",        "Lt. Lorrir",            "lieutenantlorrir",       "TIE Interceptor",            "tieinterceptor",           "I", mTIEIN, true,  5, 3, 3, 3, 0, 23, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT,           } },
  { Faction::Empire, BaseSize::Small, "Royal Guard Pilot",        "Royal Guard Pilot",     "royalguardpilot",        "TIE Interceptor",            "tieinterceptor",           "I", mTIEIN, false, 6, 3, 3, 3, 0, 22, Act::Focus|Act::BarrelRoll|Act::Boost|Act::Evade,      {MT, Upg::Elite} },

  { Faction::Rebel,  BaseSize::Small, "Jan Ors",                  "Jan Ors",               "janors",                 "HWK-290",                    "hwk290",                   "h", mHWK29, true,  8, 1, 2, 4, 1, 25, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Cannon, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Small, "Kyle Katarn",              "Kyle Katarn",           "kylekatarn",             "HWK-290",                    "hwk290",                   "h", mHWK29, true,  6, 1, 2, 4, 1, 21, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Cannon, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Small, "Roark Garnet",             "Roark Garnet",          "roarkgarnet",            "HWK-290",                    "hwk290",                   "h", mHWK29, true,  4, 1, 2, 4, 1, 19, Act::Focus|Act::TargetLock,                            {MT,             Upg::Cannon, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Small, "Rebel Operative",          "Rebel Operative",       "rebeloperative",         "HWK-290",                    "hwk290",                   "h", mHWK29, false, 2, 1, 2, 4, 1, 16, Act::Focus|Act::TargetLock,                            {MT,             Upg::Cannon, Upg::Crew} },

  { Faction::Empire, BaseSize::Large, "Captain Kagi",             "Capt. Kagi",            "captainkagi",            "Lambda-class Shuttle",       "lambdaclassshuttle",       "l", mLAMBD, true,  8, 3, 1, 5, 5, 27, Act::Focus|Act::TargetLock,                            {MT, Upg::System, Upg::Cannon, Upg::Crew, Upg::Crew} },
  { Faction::Empire, BaseSize::Large, "Captain Yorr",             "Capt. Yorr",            "captainyorr",            "Lambda-class Shuttle",       "lambdaclassshuttle",       "l", mLAMBD, true,  4, 3, 1, 5, 5, 24, Act::Focus|Act::TargetLock,                            {MT, Upg::System, Upg::Cannon, Upg::Crew, Upg::Crew} },
  { Faction::Empire, BaseSize::Large, "Colonel Jendon",           "Col. Jendon",           "coloneljendon",          "Lambda-class Shuttle",       "lambdaclassshuttle",       "l", mLAMBD, true,  6, 3, 1, 5, 5, 26, Act::Focus|Act::TargetLock,                            {MT, Upg::System, Upg::Cannon, Upg::Crew, Upg::Crew} },
  { Faction::Empire, BaseSize::Large, "Omicron Group Pilot",      "Omicron Grp Pilot",     "omicrongrouppilot",      "Lambda-class Shuttle",       "lambdaclassshuttle",       "l", mLAMBD, false, 2, 3, 1, 5, 5, 21, Act::Focus|Act::TargetLock,                            {MT, Upg::System, Upg::Cannon, Upg::Crew, Upg::Crew} },

  { Faction::Rebel,  BaseSize::Small, "Ten Numb",                 "Ten Numb",              "tennumb",                "B-Wing",                     "bwing",                    "b", mBWING, true,  8, 3, 1, 3, 5, 31, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Torpedo, Upg::Torpedo} },
  { Faction::Rebel,  BaseSize::Small, "Ibtisam",                  "Ibtisam",               "ibtisam",                "B-Wing",                     "bwing",                    "b", mBWING, true,  6, 3, 1, 3, 5, 28, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Torpedo, Upg::Torpedo} },
  { Faction::Rebel,  BaseSize::Small, "Dagger Squadron Pilot",    "Dagger Sq. Pilot",      "daggersquadronpilot",    "B-Wing",                     "bwing",                    "b", mBWING, false, 4, 3, 1, 3, 5, 24, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Torpedo, Upg::Torpedo} },
  { Faction::Rebel,  BaseSize::Small, "Blue Squadron Pilot",      "Blue Sq. Pilot",        "bluesquadronpilot",      "B-Wing",                     "bwing",                    "b", mBWING, false, 2, 3, 1, 3, 5, 22, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Torpedo, Upg::Torpedo} },
  { Faction::Rebel,  BaseSize::Small, "Keyan Farlander",          "Keyan Farlander",       "keyanfarlander",         "B-Wing",                     "bwing",                    "b", mBWING, true,  7, 3, 1, 3, 5, 29, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Torpedo, Upg::Torpedo} },
  { Faction::Rebel,  BaseSize::Small, "Nera Dantels",             "Nera Dantels",          "neradantels",            "B-Wing",                     "bwing",                    "b", mBWING, true,  5, 3, 1, 3, 5, 26, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Torpedo, Upg::Torpedo} },

  { Faction::Empire, BaseSize::Small, "Major Rhymer",             "Maj. Rhymer",           "majorrhymer",            "TIE Bomber",                 "tiebomber",                "B", mTIEBO, true,  7, 2, 2, 6, 0, 26, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb} },
  { Faction::Empire, BaseSize::Small, "Captain Jonus",            "Capt. Jonus",           "captainjonus",           "TIE Bomber",                 "tiebomber",                "B", mTIEBO, true,  6, 2, 2, 6, 0, 22, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb} },
  { Faction::Empire, BaseSize::Small, "Gamma Squadron Pilot",     "Gamma Sq. Pilot",       "gammasquadronpilot",     "TIE Bomber",                 "tiebomber",                "B", mTIEBO, false, 4, 2, 2, 6, 0, 18, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT,             Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb} },
  { Faction::Empire, BaseSize::Small, "Schimitar Squadron Pilot", "Schimitar Sq. Pilot",   "schimitarsquadronpilot", "TIE Bomber",                 "tiebomber",                "B", mTIEBO, false, 2, 2, 2, 6, 0, 16, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT,             Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb} },
  { Faction::Empire, BaseSize::Small, "Tomax Bren",               "Tomax Bren",            "tomaxbren",              "TIE Bomber",                 "tiebomber",                "B", mTIEBO, true,  8, 2, 2, 6, 0, 24, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb} },
  { Faction::Empire, BaseSize::Small, "\"Deathfire\"",            "Deathfire",             "deathfire",              "TIE Bomber",                 "tiebomber",                "B", mTIEBO, true,  3, 2, 2, 6, 0, 17, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT,             Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb} },
  { Faction::Empire, BaseSize::Small, "Gamma Squadron Veteran",   "Gamma Sq. Vet.",        "gammasquadronveteran",   "TIE Bomber",                 "tiebomber",                "B", mTIEBO, false, 5, 2, 2, 6, 0, 19, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb} },

  { Faction::Rebel,  BaseSize::Small, "Airen Cracken",            "Airen Cracken",         "airencracken",           "Z-95 Headhunter",            "z95headhunter",            "z", mZ95HH, true,  8, 2, 2, 2, 2, 19, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile} },
  { Faction::Rebel,  BaseSize::Small, "Lieutenant Blount",        "Lt. Blount",            "lieutenantblout",        "Z-95 Headhunter",            "z95headhunter",            "z", mZ95HH, true,  6, 2, 2, 2, 2, 17, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile} },
  { Faction::Rebel,  BaseSize::Small, "Tala Squadron Pilot",      "Tala Sq. Pilot",        "talasquadronpilot",      "Z-95 Headhunter",            "z95headhunter",            "z", mZ95HH, false, 4, 2, 2, 2, 2, 13, Act::Focus|Act::TargetLock,                            {MT,             Upg::Missile} },
  { Faction::Rebel,  BaseSize::Small, "Bandit Squadron Pilot",    "Bandit Sq. Pilot",      "banditsquadronpilot",    "Z-95 Headhunter",            "z95headhunter",            "z", mZ95HH, false, 2, 2, 2, 2, 2, 12, Act::Focus|Act::TargetLock,                            {MT,             Upg::Missile} },

  { Faction::Empire, BaseSize::Small, "Rexler Brath",             "Rexler Brath",          "rexlerbrath",            "TIE Defender",               "tiedefender",              "D", mTIEDE, true,  8, 3, 3, 3, 3, 37, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Cannon, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Colonel Vessery",          "Col. Vessery",          "colonelvessery",         "TIE Defender",               "tiedefender",              "D", mTIEDE, true,  6, 3, 3, 3, 3, 35, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Cannon, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Onyx Squadron Pilot",      "Onyx Sq. Pilot",        "onyxsquadronpilot",      "TIE Defender",               "tiedefender",              "D", mTIEDE, false, 3, 3, 3, 3, 3, 32, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT,             Upg::Cannon, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Delta Squadron Pilot",     "Delta Sq. Pilot",       "deltasquadronpilot",     "TIE Defender",               "tiedefender",              "D", mTIEDE, false, 1, 3, 3, 3, 3, 30, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT,             Upg::Cannon, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Maarek Stele",             "Maarek Steele",         "maarekstele",            "TIE Defender",               "tiedefender",              "D", mTIEDE, true,  7, 3, 3, 3, 3, 35, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Cannon, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Countess Ryad",            "Countess Ryad",         "countessryad",           "TIE Defender",               "tiedefender",              "D", mTIEDE, true,  5, 3, 3, 3, 3, 34, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Cannon, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Glaive Squadron Pilot",    "Glaive Sq. Pilot",      "glaivesquadronpilot",    "TIE Defender",               "tiedefender",              "D", mTIEDE, false, 6, 3, 3, 3, 3, 34, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Cannon, Upg::Missile} },

  { Faction::Rebel,  BaseSize::Small, "Corran Horn",              "Corran Horn",           "corranhorn",             "E-Wing",                     "ewing",                    "e", mEWING, true,  8, 3, 3, 2, 3, 35, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::System, Upg::Torpedo, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Etahn A'baht",             "Etahn A'baht",          "etahnabaht",             "E-Wing",                     "ewing",                    "e", mEWING, true,  5, 3, 3, 2, 3, 32, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::System, Upg::Torpedo, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Blackmoon Squadron Pilot", "Blackmoon Sq. Pilot",   "blackmoonsquadronpilot", "E-Wing",                     "ewing",                    "e", mEWING, false, 3, 3, 3, 2, 3, 29, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,             Upg::System, Upg::Torpedo, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Knave Squadron Pilot",     "Knave Sq. Pilot",       "knavesquadronpilot",     "E-Wing",                     "ewing",                    "e", mEWING, false, 1, 3, 3, 2, 3, 27, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,             Upg::System, Upg::Torpedo, Upg::Astromech} },

  { Faction::Empire, BaseSize::Small, "\"Whisper\"",              "Whisper",               "whisper",                "TIE Phantom",                "tiephantom",               "P", mTIEPH, true,  7, 4, 2, 2, 2, 32, Act::Focus|Act::BarrelRoll|Act::Evade|Act::Cloak,      {MT, Upg::Elite, Upg::System, Upg::Crew} },
  { Faction::Empire, BaseSize::Small, "\"Echo\"",                 "Echo",                  "echo",                   "TIE Phantom",                "tiephantom",               "P", mTIEPH, true,  6, 4, 2, 2, 2, 30, Act::Focus|Act::BarrelRoll|Act::Evade|Act::Cloak,      {MT, Upg::Elite, Upg::System, Upg::Crew} },
  { Faction::Empire, BaseSize::Small, "Shadow Squadron Pilot",    "Shadow Sq. Pilot",      "shadowsquadronpilot",    "TIE Phantom",                "tiephantom",               "P", mTIEPH, false, 5, 4, 2, 2, 2, 27, Act::Focus|Act::BarrelRoll|Act::Evade|Act::Cloak,      {MT,             Upg::System, Upg::Crew} },
  { Faction::Empire, BaseSize::Small, "Sigma Squadron Pilot",     "Signa Sq. Pilot",       "sigmasquadronpilot",     "TIE Phantom",                "tiephantom",               "P", mTIEPH, false, 3, 4, 2, 2, 2, 25, Act::Focus|Act::BarrelRoll|Act::Evade|Act::Cloak,      {MT,             Upg::System, Upg::Crew} },

  { Faction::Rebel,  BaseSize::Large, "Dash Rendar",              "Dash Rendar",           "dashrendar",             "YT-2400 Freighter",          "yt2400",                   "o", mYT240, true,  7, 2, 2, 5, 5, 36, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Cannon, Upg::Missile, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "\"Leebo\"",                "Leebo",                 "leebo",                  "YT-2400 Freighter",          "yt2400",                   "o", mYT240, true,  5, 2, 2, 5, 5, 34, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Cannon, Upg::Missile, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Eaden Vrill",              "Eaden Vrill",           "eadenvrill",             "YT-2400 Freighter",          "yt2400",                   "o", mYT240, true,  3, 2, 2, 5, 5, 32, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT,             Upg::Cannon, Upg::Missile, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Wild Space Fringer",       "Wild Space Fringer",    "wildspacefringer",       "YT-2400 Freighter",          "yt2400",                   "o", mYT240, false, 2, 2, 2, 5, 5, 30, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT,             Upg::Cannon, Upg::Missile, Upg::Crew} },

  { Faction::Empire, BaseSize::Large, "Rear Admiral Chiraneau",   "RADM. Chiraneau",       "rearadmiralchiraneau",   "VT-49 Decimator",            "vt49decimator",            "d", mVT49D, true,  8, 3, 0,12, 4, 46, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Torpedo, Upg::Crew, Upg::Crew, Upg::Crew, Upg::Bomb} },
  { Faction::Empire, BaseSize::Large, "Commander Kenkirk",        "Cmdr. Kenkirk",         "commanderkenkirk",       "VT-49 Decimator",            "vt49decimator",            "d", mVT49D, true,  6, 3, 0,12, 4, 44, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Torpedo, Upg::Crew, Upg::Crew, Upg::Crew, Upg::Bomb} },
  { Faction::Empire, BaseSize::Large, "Captain Oicunn",           "Capt Oicunn",           "captainoicunn",          "VT-49 Decimator",            "vt49decimator",            "d", mVT49D, true,  4, 3, 0,12, 4, 42, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Torpedo, Upg::Crew, Upg::Crew, Upg::Crew, Upg::Bomb} },
  { Faction::Empire, BaseSize::Large, "Patrol Leader",            "Patrol Leader",         "patrolleader",           "VT-49 Decimator",            "vt49decimator",            "d", mVT49D, false, 3, 3, 0,12, 4, 40, Act::Focus|Act::TargetLock,                            {MT,             Upg::Torpedo, Upg::Crew, Upg::Crew, Upg::Crew, Upg::Bomb} },

  { Faction::Scum,   BaseSize::Small, "Kavil",                    "Kavil",                 "kavil",                  "Y-Wing",                     "ywing",                    "y", mYWING, true,  7, 2, 1, 5, 3, 24, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::SalvagedAstromech} },
  { Faction::Scum,   BaseSize::Small, "Drea Renthal",             "Drea Renthal",          "drearenthal",            "Y-Wing",                     "ywing",                    "y", mYWING, true,  5, 2, 1, 5, 3, 22, Act::Focus|Act::TargetLock,                            {MT,             Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::SalvagedAstromech} },
  { Faction::Scum,   BaseSize::Small, "Hired Gun",                "Hired Gun",             "hiredgun",               "Y-Wing",                     "ywing",                    "y", mYWING, false, 4, 2, 1, 5, 3, 20, Act::Focus|Act::TargetLock,                            {MT,             Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::SalvagedAstromech} },
  { Faction::Scum,   BaseSize::Small, "Syndicate Thug",           "Syndicate Thug",        "syndicatethug",          "Y-Wing",                     "ywing",                    "y", mYWING, false, 2, 2, 1, 5, 3, 18, Act::Focus|Act::TargetLock,                            {MT,             Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::SalvagedAstromech} },

  { Faction::Scum,   BaseSize::Large, "Boba Fett",                "Boba Fett",             "bobafett",               "Firespray-31",               "firespray31",              "f", mFSP31, true,  8, 3, 2, 6, 4, 39, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::Elite, Upg::Cannon, Upg::Bomb, Upg::Crew, Upg::Missile, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Kath Scarlet",             "Kath Scarlet",          "kathscarlet",            "Firespray-31",               "firespray31",              "f", mFSP31, true,  7, 3, 2, 6, 4, 38, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::Elite, Upg::Cannon, Upg::Bomb, Upg::Crew, Upg::Missile, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Emon Azzameen",            "Emon Azzameen",         "emonazzameen",           "Firespray-31",               "firespray31",              "f", mFSP31, true,  6, 3, 2, 6, 4, 36, Act::Focus|Act::TargetLock|Act::Evade,                 {MT,             Upg::Cannon, Upg::Bomb, Upg::Crew, Upg::Missile, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Mandalorian Mercenary",    "Mandalorian Merc.",     "mandalorianmercenary",   "Firespray-31",               "firespray31",              "f", mFSP31, false, 5, 3, 2, 6, 4, 35, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::Elite, Upg::Cannon, Upg::Bomb, Upg::Crew, Upg::Missile, Upg::Illicit} },

  { Faction::Scum,   BaseSize::Small, "Dace Bonearm",             "Dace Bonearm",          "dacebonearm",            "HWK-290",                    "hwk290",                   "h", mHWK29, true,  7, 1, 2, 4, 1, 23, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Cannon, Upg::Crew, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Palob Godalhi",            "Palob Godalhi",         "palobgodalhi",           "HWK-290",                    "hwk290",                   "h", mHWK29, true,  5, 1, 2, 4, 1, 20, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Cannon, Upg::Crew, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Torkil Mux",               "Torkil Mux",            "torkilmux",              "HWK-290",                    "hwk290",                   "h", mHWK29, true,  3, 1, 2, 4, 1, 19, Act::Focus|Act::TargetLock,                            {MT,             Upg::Cannon, Upg::Crew, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Spice Runner",             "Spice Runner",          "spicerunner",            "HWK-290",                    "hwk290",                   "h", mHWK29, false, 1, 1, 2, 4, 1, 16, Act::Focus|Act::TargetLock,                            {MT,             Upg::Cannon, Upg::Crew, Upg::Illicit} },

  { Faction::Scum,   BaseSize::Small, "N'Dru Suhlak",             "N'Dru Suhlak",          "ndrusuhlak",             "Z-95 Headhunter",            "z95headhunter",            "z", mZ95HH, true,  7, 2, 2, 2, 2, 17, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Kaa'to Leeachos",          "Kaa'to Leeachos",       "kaatoleeachos",          "Z-95 Headhunter",            "z95headhunter",            "z", mZ95HH, true,  5, 2, 2, 2, 2, 15, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Black Sun Soldier",        "Black Sun Soldier",     "blacksunsoldier",        "Z-95 Headhunter",            "z95headhunter",            "z", mZ95HH, false, 3, 2, 2, 2, 2, 13, Act::Focus|Act::TargetLock,                            {MT,             Upg::Missile, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Binayre Pirate",           "Binayre Pirate",        "binayrepirate",          "Z-95 Headhunter",            "z95headhunter",            "z", mZ95HH, false, 1, 2, 2, 2, 2, 12, Act::Focus|Act::TargetLock,                            {MT,             Upg::Missile, Upg::Illicit} },

  { Faction::Scum,   BaseSize::Small, "Laetin A'shera",           "Laetin A'shera",        "laetinashera",           "M3-A Scyk Interceptor",      "m3ainterceptor",           "s", mM3AIN, true,  6, 2, 3, 2, 1, 18, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,           } }, 
  { Faction::Scum,   BaseSize::Small, "Serissu",                  "Serissu",               "serissu",                "M3-A Scyk Interceptor",      "m3ainterceptor",           "s", mM3AIN, true,  8, 2, 3, 2, 1, 20, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite} },
  { Faction::Scum,   BaseSize::Small, "Tansarii Point Veteran",   "Tansarii Point Vet.",   "tansariipointveteran",   "M3-A Scyk Interceptor",      "m3ainterceptor",           "s", mM3AIN, false, 5, 2, 3, 2, 1, 17, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite} },
  { Faction::Scum,   BaseSize::Small, "Cartel Spacer",            "Cartel Spacer",         "cartelspacer",           "M3-A Scyk Interceptor",      "m3ainterceptor",           "s", mM3AIN, false, 2, 2, 3, 2, 1, 14, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,           } },

  { Faction::Scum,   BaseSize::Small, "Prince Xizor",             "Prince Xizor",          "princexizor",            "StarViper",                  "starviper",                "v", mSTARV, true,  7, 3, 3, 4, 1, 31, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Torpedo} },
  { Faction::Scum,   BaseSize::Small, "Guri",                     "Guri",                  "guri",                   "StarViper",                  "starviper",                "v", mSTARV, true,  5, 3, 3, 4, 1, 30, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Torpedo} },
  { Faction::Scum,   BaseSize::Small, "Black Sun Vigo",           "Black Sun Vigo",        "blacksunvigo",           "StarViper",                  "starviper",                "v", mSTARV, false, 3, 3, 3, 4, 1, 27, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT,             Upg::Torpedo} },
  { Faction::Scum,   BaseSize::Small, "Black Sun Enforcer",       "Black Sun Enforcer",    "blacksunenforcer",       "StarViper",                  "starviper",                "v", mSTARV, false, 1, 3, 3, 4, 1, 25, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT,             Upg::Torpedo} },

  { Faction::Scum,   BaseSize::Large, "IG-88A",                   "IG-88A",                "ig88a",                  "IG-2000",                    "aggressor",                "i", mAGGRE, true,  6, 3, 3, 4, 4, 36, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Cannon, Upg::Bomb, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "IG-88B",                   "IG-88B",                "ig88b",                  "IG-2000",                    "aggressor",                "i", mAGGRE, true,  6, 3, 3, 4, 4, 36, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Cannon, Upg::Bomb, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "IG-88C",                   "IG-88C",                "ig88c",                  "IG-2000",                    "aggressor",                "i", mAGGRE, true,  6, 3, 3, 4, 4, 36, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Cannon, Upg::Bomb, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "IG-88D",                   "IG-88D",                "ig88d",                  "IG-2000",                    "aggressor",                "i", mAGGRE, true,  6, 3, 3, 4, 4, 36, Act::Focus|Act::TargetLock|Act::Boost|Act::Evade,      {MT, Upg::Elite, Upg::System, Upg::Cannon, Upg::Cannon, Upg::Bomb, Upg::Illicit} },

  { Faction::Scum,   BaseSize::Large, "Bossk",                    "Bossk",                 "bossk",                  "YV-666 Freighter",           "yv666",                    "t", mYV666, true,  7, 3, 1, 6, 6, 35, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Cannon, Upg::Missile, Upg::Crew, Upg::Crew, Upg::Crew, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Latts Razzi",              "Latts Razzi",           "lattsrazzi",             "YV-666 Freighter",           "yv666",                    "t", mYV666, true,  5, 3, 1, 6, 6, 33, Act::Focus|Act::TargetLock,                            {MT,             Upg::Cannon, Upg::Missile, Upg::Crew, Upg::Crew, Upg::Crew, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Moralo Eval",              "Moralo Eval",           "moraloeval",             "YV-666 Freighter",           "yv666",                    "t", mYV666, true,  6, 3, 1, 6, 6, 34, Act::Focus|Act::TargetLock,                            {MT,             Upg::Cannon, Upg::Missile, Upg::Crew, Upg::Crew, Upg::Crew, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Trandoshan Slaver",        "Trandoshan Slaver",     "trandoshanslaver",       "YV-666 Freighter",           "yv666",                    "t", mYV666, false, 2, 3, 1, 6, 6, 29, Act::Focus|Act::TargetLock,                            {MT,             Upg::Cannon, Upg::Missile, Upg::Crew, Upg::Crew, Upg::Crew, Upg::Illicit} },

  { Faction::Scum,   BaseSize::Small, "Talonbane Cobra",          "Talonbane Cobra",       "talonbanecobra",         "Kihraxz Fighter",            "kihraxzfighter",           "r", mKIHRA, true,  9, 3, 2, 4, 1, 28, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Graz the Hunter",          "Graz the Hunter",       "grazthehunter",          "Kihraxz Fighter",            "kihraxzfighter",           "r", mKIHRA, true,  6, 3, 2, 4, 1, 25, Act::Focus|Act::TargetLock,                            {MT,             Upg::Missile, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Black Sun Ace",            "Black Sun Ace",         "blacksunace",            "Kihraxz Fighter",            "kihraxzfighter",           "r", mKIHRA, false, 5, 3, 2, 4, 1, 23, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Missile, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Cartel Marauder",          "Cartel Marauder",       "cartelmarauder",         "Kihraxz Fighter",            "kihraxzfighter",           "r", mKIHRA, false, 2, 3, 2, 4, 1, 20, Act::Focus|Act::TargetLock,                            {MT,             Upg::Missile, Upg::Illicit} },

  { Faction::Rebel,  BaseSize::Small, "Miranda Doni",             "Miranda Doni",          "mirandadoni",            "K-Wing",                     "kwing",                    "k", mKWING, true,  8, 2, 1, 5, 4, 29, Act::Focus|Act::TargetLock|Act::SLAM,                  {MT, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Crew, Upg::Bomb, Upg::Bomb} },
  { Faction::Rebel,  BaseSize::Small, "Esege Tuketu",             "Esege Tuketu",          "esegetuketu",            "K-Wing",                     "kwing",                    "k", mKWING, true,  6, 2, 1, 5, 4, 28, Act::Focus|Act::TargetLock|Act::SLAM,                  {MT, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Crew, Upg::Bomb, Upg::Bomb} },
  { Faction::Rebel,  BaseSize::Small, "Guardian Squadron Pilot",  "Guardian Sq. Pilot",    "guardiansquadronpilot",  "K-Wing",                     "kwing",                    "k", mKWING, false, 4, 2, 1, 5, 4, 25, Act::Focus|Act::TargetLock|Act::SLAM,                  {MT, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Crew, Upg::Bomb, Upg::Bomb} },
  { Faction::Rebel,  BaseSize::Small, "Warden Squadron Pilot",    "Warden Sq. Pilot",      "wardensquadronpilot",    "K-Wing",                     "kwing",                    "k", mKWING, false, 2, 2, 1, 5, 4, 23, Act::Focus|Act::TargetLock|Act::SLAM,                  {MT, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Crew, Upg::Bomb, Upg::Bomb} },

  { Faction::Empire, BaseSize::Small, "\"Redline\"",              "Redline",               "redline",                "TIE Punisher",               "tiepunisher",              "N", mTIEPU, true,  7, 2, 1, 6, 3, 27, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::System, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb, Upg::Bomb} },
  { Faction::Empire, BaseSize::Small, "\"Deathrain\"",            "Deathrain",             "deathrain",              "TIE Punisher",               "tiepunisher",              "N", mTIEPU, true,  6, 2, 1, 6, 3, 26, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::System, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb, Upg::Bomb} },
  { Faction::Empire, BaseSize::Small, "Black Eight Sq. Pilot",    "Black Eight Sq. Pilot", "blackeightsqpilot",      "TIE Punisher",               "tiepunisher",              "N", mTIEPU, false, 4, 2, 1, 6, 3, 23, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::System, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb, Upg::Bomb} },
  { Faction::Empire, BaseSize::Small, "Cutlass Squadron Pilot",   "Cutlass Sq. Pilot",     "cutlasssquadronpilot",   "TIE Punisher",               "tiepunisher",              "N", mTIEPU, false, 2, 2, 1, 6, 3, 21, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::System, Upg::Torpedo, Upg::Torpedo, Upg::Missile, Upg::Missile, Upg::Bomb, Upg::Bomb} },

  { Faction::Rebel,  BaseSize::Large, "Hera Syndulla",            "Hera Syndulla",         "herasyndulla",           "VCX-100",                    "vcx100",                   "G", mVCX10, true,  7, 4, 0,10, 6, 40, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::System, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Kanan Jarrus",             "Kanan Jarrus",          "kananjarrus",            "VCX-100",                    "vcx100",                   "G", mVCX10, true,  5, 4, 0,10, 6, 38, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::System, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "\"Chopper\"",              "Chopper",               "chopper",                "VCX-100",                    "vcx100",                   "G", mVCX10, true,  4, 4, 0,10, 6, 37, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::System, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Lothal Rebel",             "Lothal Rebel",          "lothalrebel",            "VCX-100",                    "vcx100",                   "G", mVCX10, false, 3, 4, 0,10, 6, 35, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::System, Upg::Turret, Upg::Torpedo, Upg::Torpedo, Upg::Crew, Upg::Crew} },

  { Faction::Rebel,  BaseSize::Small, "Hera Syndulla",            "Hera Syndula",          "herasyndulla",           "Attack Shuttle",             "attackshuttle",            "g", mATTAC, true,  7, 3, 2, 2, 2, 22, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite, Upg::Turret, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Small, "Sabine Wren",              "Sabine Wren",           "sabinewren",             "Attack Shuttle",             "attackshuttle",            "g", mATTAC, true,  5, 3, 2, 2, 2, 21, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite, Upg::Turret, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Small, "Ezra Bridger",             "Ezra Bridger",          "ezrabridger",            "Attack Shuttle",             "attackshuttle",            "g", mATTAC, true,  4, 3, 2, 2, 2, 20, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite, Upg::Turret, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Small, "\"Zeb\" Orrelios",         "Zeb Orrelios",          "zeborrelios",            "Attack Shuttle",             "attackshuttle",            "g", mATTAC, true,  3, 3, 2, 2, 2, 18, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT,             Upg::Turret, Upg::Crew} },

  { Faction::Empire, BaseSize::Small, "The Inquisitor",           "The Inquisitor",         "theinquisitor",          "TIE Advanced Prototype",     "tieadvancedprototype",    "R", mTIEAP, true,  8, 2, 3, 2, 2, 25, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Valen Rudor",              "Valen Rudor",            "valenrudor",             "TIE Advanced Prototype",     "tieadvancedprototype",    "R", mTIEAP, true,  6, 2, 3, 2, 2, 22, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Baron of the Empire",      "Baron of the Empire",    "baronoftheempire",       "TIE Advanced Prototype",     "tieadvancedprototype",    "R", mTIEAP, false, 4, 2, 3, 2, 2, 19, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Missile} },
  { Faction::Empire, BaseSize::Small, "Sienar Test Pilot",        "Sienar Test Pilot",      "sienartestpilot",        "TIE Advanced Prototype",     "tieadvancedprototype",    "R", mTIEAP, false, 2, 2, 3, 2, 2, 16, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT,             Upg::Missile} },

  { Faction::Scum,   BaseSize::Small, "Zuckuss",                  "Zuckuss",                "zuckuss",                "G-1A Starfighter",           "g1astarfighter",          "n", mG1AST, true,  7, 3, 1, 4, 4, 28, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::Elite, Upg::Crew, Upg::System, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "4-LOM",                    "4-LOM",                  "4lom",                   "G-1A Starfighter",           "g1astarfighter",          "n", mG1AST, true,  6, 3, 1, 4, 4, 27, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::Elite, Upg::Crew, Upg::System, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Gand Findsman",            "Gand Findsman",          "gandfindsman",           "G-1A Starfighter",           "g1astarfighter",          "n", mG1AST, false, 5, 3, 1, 4, 4, 25, Act::Focus|Act::TargetLock|Act::Evade,                 {MT, Upg::Elite, Upg::Crew, Upg::System, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Small, "Ruthless Freelancer",      "Ruthless Freelancer",    "ruthlessfreelancer",     "G-1A Starfighter",           "g1astarfighter",          "n", mG1AST, false, 3, 3, 1, 4, 4, 23, Act::Focus|Act::TargetLock|Act::Evade,                 {MT,             Upg::Crew, Upg::System, Upg::Illicit} },

  { Faction::Scum,   BaseSize::Large, "Dengar",                   "Dengar",                 "dengar",                 "JumpMaster 5000",            "jumpmaster5000",          "p", mJUMPM, true,  9, 2, 2, 5, 4, 33, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Torpedo, Upg::Torpedo, Upg::Crew, Upg::SalvagedAstromech, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Tel Trevura",              "Tel Rrevura",            "teltrevura",             "JumpMaster 5000",            "jumpmaster5000",          "p", mJUMPM, true,  7, 2, 2, 5, 4, 30, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Torpedo, Upg::Torpedo, Upg::Crew, Upg::SalvagedAstromech, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Manaroo",                  "Manaroo",                "manaroo",                "JumpMaster 5000",            "jumpmaster5000",          "p", mJUMPM, true,  4, 2, 2, 5, 4, 27, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Torpedo, Upg::Torpedo, Upg::Crew, Upg::SalvagedAstromech, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Contracted Scout",         "Contracted Scout",       "contractedscout",        "JumpMaster 5000",            "jumpmaster5000",          "p", mJUMPM, false, 3, 2, 2, 5, 4, 25, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::Torpedo, Upg::Torpedo, Upg::Crew, Upg::SalvagedAstromech, Upg::Illicit} },

  { Faction::Rebel,  BaseSize::Small, "Poe Dameron",              "Poe Dameron",            "poedameron",             "T-70 X-Wing Fighter",        "t70xwing",                "x", mT70XW, true,  8, 3, 2, 3, 3, 31, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech, Upg::Tech} },
  { Faction::Rebel,  BaseSize::Small, "\"Blue Ace\"",             "Blue Ace",               "blueace",                "T-70 X-Wing Fighter",        "t70xwing",                "x", mT70XW, true,  5, 3, 2, 3, 3, 27, Act::Focus|Act::TargetLock|Act::Boost,                 {MT,             Upg::Torpedo, Upg::Astromech, Upg::Tech} },
  { Faction::Rebel,  BaseSize::Small, "Red Squadron Veteran",     "Red Sq. Veteran",        "redsquadronveteran",     "T-70 X-Wing Fighter",        "t70xwing",                "x", mT70XW, false, 4, 3, 2, 3, 3, 26, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech, Upg::Tech} },
  { Faction::Rebel,  BaseSize::Small, "Blue Squadron Novice",     "Blue Sq. Novice",        "bluesquadronnovice",     "T-70 X-Wing Fighter",        "t70xwing",                "x", mT70XW, false, 2, 3, 2, 3, 3, 24, Act::Focus|Act::TargetLock|Act::Boost,                 {MT,             Upg::Torpedo, Upg::Astromech, Upg::Tech} },
  { Faction::Rebel,  BaseSize::Small, "Ello Asty",                "Ello Asty",              "elloasty",               "T-70 X-Wing Fighter",        "t70xwing",                "x", mT70XW, true,  7, 3, 2, 3, 3, 30, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech, Upg::Tech} },
  { Faction::Rebel,  BaseSize::Small, "\"Red Ace\"",              "Red Ace",                "redace",                 "T-70 X-Wing Fighter",        "t70xwing",                "x", mT70XW, true,  6, 3, 2, 3, 3, 29, Act::Focus|Act::TargetLock|Act::Boost,                 {MT,             Upg::Torpedo, Upg::Astromech, Upg::Tech} },
  { Faction::Rebel,  BaseSize::Small, "Poe Dameron",              "Poe Dameron",            "poedameron-swx57",       "T-70 X-Wing Fighter",        "t70xwing",                "x", mT70XW, true,  9, 3, 2, 3, 3, 33, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech, Upg::Tech} },
  { Faction::Rebel,  BaseSize::Small, "Nien Nunb",                "Nien Nunb",              "niennunb",               "T-70 X-Wing Fighter",        "t70xwing",                "x", mT70XW, true,  7, 3, 2, 3, 3, 29, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech, Upg::Tech} },
  { Faction::Rebel,  BaseSize::Small, "\"Snap\" Wexley",          "Snap Wexley",            "snapwexley",             "T-70 X-Wing Fighter",        "t70xwing",                "x", mT70XW, true,  6, 3, 2, 3, 3, 28, Act::Focus|Act::TargetLock|Act::Boost,                 {MT, Upg::Elite, Upg::Torpedo, Upg::Astromech, Upg::Tech} },
  { Faction::Rebel,  BaseSize::Small, "Jess Pava",                "Jess Pava",              "jesspava",               "T-70 X-Wing Fighter",        "t70xwing",                "x", mT70XW, true,  3, 3, 2, 3, 3, 25, Act::Focus|Act::TargetLock|Act::Boost,                 {MT,             Upg::Torpedo, Upg::Astromech, Upg::Tech} },

  { Faction::Empire, BaseSize::Small, "\"Omega Ace\"",            "Omega Ace",              "omegaace",               "TIE/fo Fighter",             "tiefofighter",            "O", mTIEFO, true,  7, 2, 3, 3, 1, 20, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "\"Epsilon Leader\"",       "Epsilon Leader",         "epsilonleader",          "TIE/fo Fighter",             "tiefofighter",            "O", mTIEFO, true,  6, 2, 3, 3, 1, 19, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,             Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "\"Zeta Ace",               "Zeta Ace",               "zetaace",                "TIE/fo Fighter",             "tiefofighter",            "O", mTIEFO, true,  5, 2, 3, 3, 1, 18, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "Omega Squadron Pilot",     "Omega Sq. Pilot",        "omegasquadronpilot",     "TIE/fo Fighter",             "tiefofighter",            "O", mTIEFO, false, 4, 2, 3, 3, 1, 17, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "Zeta Squadron Pilot",      "Zeta Sq. Pilot",         "zetasquadronpilot",      "TIE/fo Fighter",             "tiefofighter",            "O", mTIEFO, false, 3, 2, 3, 3, 1, 16, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,             Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "Epsilon Squadron Pilot",   "Epsilon Sq. Pilot",      "epsilonsquadronpilot",   "TIE/fo Fighter",             "tiefofighter",            "O", mTIEFO, false, 1, 2, 3, 3, 1, 15, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,             Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "\"Omega Leader",           "Omega Leader",           "omegaleader",            "TIE/fo Fighter",             "tiefofighter",            "O", mTIEFO, true,  8, 2, 3, 3, 1, 21, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "\"Zeta Leader",            "Zeta Leader",            "zetaleader",             "TIE/fo Fighter",             "tiefofighter",            "O", mTIEFO, true,  7, 2, 3, 3, 1, 20, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT, Upg::Elite, Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "\"Epsilon Ace",            "Epsilon Ace",            "epsilonace",             "TIE/fo Fighter",             "tiefofighter",            "O", mTIEFO, true,  4, 2, 3, 3, 1, 17, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Evade, {MT,             Upg::Tech} },

  { Faction::Rebel,  BaseSize::Small, "Norra Wexley",             "Norra Wexley",           "norrawexley",            "ARC-170",                    "arc170",                  "c", mARC17, true,  7, 2, 1, 6, 3, 29, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Torpedo, Upg::Crew, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Shara Bey",                "Shara Bey",              "sharabey",               "ARC-170",                    "arc170",                  "c", mARC17, true,  6, 2, 1, 6, 3, 28, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::Torpedo, Upg::Crew, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Thane Kyrell",             "Thane Kyrell",           "thanekyrell",            "ARC-170",                    "arc170",                  "c", mARC17, true,  4, 2, 1, 6, 3, 26, Act::Focus|Act::TargetLock,                            {MT,             Upg::Torpedo, Upg::Crew, Upg::Astromech} },
  { Faction::Rebel,  BaseSize::Small, "Braylen Stramm",           "Braylen Stramm",         "braylenstramm",          "ARC-170",                    "arc170",                  "c", mARC17, true,  3, 2, 1, 6, 3, 25, Act::Focus|Act::TargetLock,                            {MT,             Upg::Torpedo, Upg::Crew, Upg::Astromech} },

  { Faction::Empire, BaseSize::Small, "\"Quickdraw\"",            "Quickdraw",              "quickdraw",              "TIE/sf Fighter",             "tiesffighter",            "S", mTIESF, true,  9, 2, 2, 3, 3, 29, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::System, Upg::Missile, Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "\"Backdraft\"",            "Backdraft",              "backdraft",              "TIE/sf Fighter",             "tiesffighter",            "S", mTIESF, true,  7, 2, 2, 3, 3, 27, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::System, Upg::Missile, Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "Omega Specialist",         "Omega Specialist",       "omegaspecialist",        "TIE/sf Fighter",             "tiesffighter",            "S", mTIESF, false, 5, 2, 2, 3, 3, 25, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT, Upg::Elite, Upg::System, Upg::Missile, Upg::Tech} },
  { Faction::Empire, BaseSize::Small, "Zeta Specialist",          "Zeta Specialist",        "zetaspecialist",         "TIE/sf Fighter",             "tiesffighter",            "S", mTIESF, false, 3, 2, 2, 3, 3, 23, Act::Focus|Act::TargetLock|Act::BarrelRoll,            {MT,             Upg::System, Upg::Missile, Upg::Tech} },

  { Faction::Scum,   BaseSize::Small, "Fenn Rau",                 "Fenn Rau",               "fennrau",                "Protectorate Starfighter",   "protectoratestarfighter", "M", mPROTE, true,  9, 3, 3, 4, 0, 28, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Torpedo} },
  { Faction::Scum,   BaseSize::Small, "Old Teroch",               "Old Teroch",             "oldteroch",              "Protectorate Starfighter",   "protectoratestarfighter", "M", mPROTE, true,  7, 3, 3, 4, 0, 26, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Torpedo} },
  { Faction::Scum,   BaseSize::Small, "Kad Solus",                "Kad Solus",              "kadsolus",               "Protectorate Starfighter",   "protectoratestarfighter", "M", mPROTE, true,  6, 3, 3, 4, 0, 25, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Torpedo} },
  { Faction::Scum,   BaseSize::Small, "Concord Dawn Ace",         "Concord Dawn Ace",       "concorddawnace",         "Protectorate Starfighter",   "protectoratestarfighter", "M", mPROTE, false, 5, 3, 3, 4, 0, 23, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Torpedo} },
  { Faction::Scum,   BaseSize::Small, "Concord Dawn Veteran",     "Concord Dawn Vet.",      "concorddawnveteran",     "Protectorate Starfighter",   "protectoratestarfighter", "M", mPROTE, false, 3, 3, 3, 4, 0, 22, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT, Upg::Elite, Upg::Torpedo} },
  { Faction::Scum,   BaseSize::Small, "Zealous Recruit",          "Zealous Recruit",        "zealousrecruit",         "Protectorate Starfighter",   "protectoratestarfighter", "M", mPROTE, false, 1, 3, 3, 4, 0, 20, Act::Focus|Act::TargetLock|Act::BarrelRoll|Act::Boost, {MT,             Upg::Torpedo} },

  { Faction::Scum,   BaseSize::Large, "Ketsu Onyo",               "Ketsy Onyo",             "ketsuonyo",              "Lancer-class Pursuit Craft", "lancerclasspursuitcraft", "L", mLANCE, true,  7, 3, 2, 7, 3, 38, Act::Focus|Act::TargetLock|Act::Evade|Act::RotateArc,  {MT, Upg::Elite, Upg::Crew, Upg::Illicit, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Asajj Ventress",           "Asajj Ventress",         "asajjventress",          "Lancer-class Pursuit Craft", "lancerclasspursuitcraft", "L", mLANCE, true,  6, 3, 2, 7, 3, 37, Act::Focus|Act::TargetLock|Act::Evade|Act::RotateArc,  {MT, Upg::Elite, Upg::Crew, Upg::Illicit, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Sabine Wren",              "Sabine Wren",            "sabinewren",             "Lancer-class Pursuit Craft", "lancerclasspursuitcraft", "L", mLANCE, true,  5, 3, 2, 7, 3, 35, Act::Focus|Act::TargetLock|Act::Evade|Act::RotateArc,  {MT,             Upg::Crew, Upg::Illicit, Upg::Illicit} },
  { Faction::Scum,   BaseSize::Large, "Shadowport Hunter",        "Shadowport Hunter",      "shadowporthunter",       "Lancer-class Pursuit Craft", "lancerclasspursuitcraft", "L", mLANCE, false, 2, 3, 2, 7, 3, 33, Act::Focus|Act::TargetLock|Act::Evade|Act::RotateArc,  {MT,             Upg::Crew, Upg::Illicit, Upg::Illicit} },

  { Faction::Rebel,  BaseSize::Large, "Cassian Andor",            "Cassian Andor",          "cassianandor",           "U-Wing",                     "uwing",                   "u", mUWING, true,  6, 3, 1, 4, 4, 27, Act::Focus|Act::TargetLock,                            {MT, Upg::Elite, Upg::System, Upg::Torpedo, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Bodhi Rook",               "Bodhi Rook",             "bodhirook",              "U-Wing",                     "uwing",                   "u", mUWING, true,  4, 3, 1, 4, 4, 25, Act::Focus|Act::TargetLock,                            {MT,             Upg::System, Upg::Torpedo, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Heff Tobber",              "Heff Tobber",            "hefftobber",             "U-Wing",                     "uwing",                   "u", mUWING, true,  3, 3, 1, 4, 4, 24, Act::Focus|Act::TargetLock,                            {MT,             Upg::System, Upg::Torpedo, Upg::Crew, Upg::Crew} },
  { Faction::Rebel,  BaseSize::Large, "Blue Squadron Pathfinder", "Blue Sq. Pathfinder",    "bluesquadronpathfinder", "U-Wing",                     "uwing",                   "u", mUWING, false, 2, 3, 1, 4, 4, 23, Act::Focus|Act::TargetLock,                            {MT,             Upg::System, Upg::Torpedo, Upg::Crew, Upg::Crew} },

  { Faction::Empire, BaseSize::Small, "\"Duchess\"",              "Duchess",                "duchess",                "TIE Striker",                "tiestriker",              "T", mTIEST, true,  8, 3, 2, 4, 0, 23, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "\"Pure Sebacc\"",          "Pure Sebacc",            "puresebacc",             "TIE Striker",                "tiestriker",              "T", mTIEST, true,  6, 3, 2, 4, 0, 22, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "\"Countdown\"",            "Countdown",              "countdown",              "TIE Striker",                "tiestriker",              "T", mTIEST, true,  5, 3, 2, 4, 0, 20, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT,           } },
  { Faction::Empire, BaseSize::Small, "Black Squadron Scout",     "Black Sq. Pilot",        "blacksquadronpilot",     "TIE Striker",                "tiestriker",              "T", mTIEST, true,  4, 3, 2, 4, 0, 20, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT, Upg::Elite} },
  { Faction::Empire, BaseSize::Small, "Scarif Defender",          "Scarif Defender",        "scarifdefender",         "TIE Striker",                "tiestriker",              "T", mTIEST, true,  3, 3, 2, 4, 0, 18, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT,           } },
  { Faction::Empire, BaseSize::Small, "Imperial Trainee",         "Imperial Trainee",       "imperialtrainss",        "TIE Striker",                "tiestriker",              "T", mTIEST, true,  1, 3, 2, 4, 0, 17, Act::Focus|Act::BarrelRoll|Act::Evade,                 {MT,           } },
};
