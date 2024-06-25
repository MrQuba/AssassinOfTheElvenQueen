#include "..\SFMLModifications\Sprite.hpp"
#pragma once
template<class E1 = Sprite, class E2 = Sprite>
class Collisions {
public:
	bool entitiesCollide(E1* ent1, E2* ent2) {
		return (*ent->getBoudingBox().intersects(*ent2->getBoudingBox())) ? true : false;
	}
private:
};
