# libxwing
C++ library for list building in FFG's X-Wing Miniatures game.



Does:
  Take an xws file return an object with all relevant info.
  Pilot objects have GetNatXXX() and GetModXXX() for Skill, Attack, etc.
    Nat returns natural values.
    Mod returns values modified by equipped upgrades.



Does Not (yet):
  Validate lists.  Give it a TIE Fighter with a Millennium Falcon title card and it's cool with it.
  Honor upgrade restrictions (rebel only, large base only, etc.)



Uses:
  jsoncpp (https://github.com/open-source-parsers/jsoncpp)



Requires:
