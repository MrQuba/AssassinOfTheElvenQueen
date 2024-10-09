#include "Character.hpp"
#pragma once

class NPC : public Character {
public:
	NPC(Path txt_path, Area txt_area) : Character(txt_path, txt_area) {}
	NPC(Path txt_path, Area txt_area, Position pos, Health health = 200) : Character(txt_path, txt_area, pos, health) {}

  virtual void AI() = 0;
};
