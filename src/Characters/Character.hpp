#include <iostream>
#include "Entity.hpp"
#include "../Logging/Logger.hpp"
#pragma once
class Character : public Entity {
public:
	Character(Path txt_path, Area txt_area) : Entity(txt_path, txt_area){}
	Character(Path txt_path, Area txt_area, Position pos) : Entity(txt_path, txt_area, pos) {}
	~Character() {}
	virtual void onCollision(Entity* ent) override { 
		if (checkIfCollidesWithAnotherEntity(ent)) Console("Collission occured");
	}
	bool checkIfCollidesWithGround(Enviroment* Enviroment) {
		return this->getBoudingBox()->intersects(Enviroment->hitbox);
	}
	bool checkIfCollidesWithAnotherEntity(Entity* ent) {
		return this->getBoudingBox()->intersects(*ent->getBoudingBox());
	}
protected:
	mutable Health base_Health = 200;
	Health current_Health = base_Health;
	std::unordered_set<Component*> drawableComponents;
	std::unordered_set<Component*> importantComponents;
};
