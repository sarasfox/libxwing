# libxwing
C++ library for list building in FFG's X-Wing Miniatures game.

**Does:**
* Take an xws file return an object with all relevant info.
* Pilot objects have GetNatXXX() and GetModXXX() for Skill, Attack, etc.
 * Nat returns natural values.
 * Mod returns values modified by equipped upgrades.
* List Validation
 * There are probably still some cards and combinations that are not handled correctly, but validation is mostly functional

**Does Not (yet):**

**Uses:**
* jsoncpp (https://github.com/open-source-parsers/jsoncpp)

**Requires:**
