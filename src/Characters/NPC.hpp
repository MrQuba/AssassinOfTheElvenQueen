#include "Character.hpp"
#pragma once

class NPC : public Character {
public:
	NPC(Path txt_path, Area txt_area) : Character(txt_path, txt_area) {}
	virtual void AI() = 0;
};
