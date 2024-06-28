#include <iostream>
#include "Entity.hpp"
#include "../Logging/Logger.hpp"
#pragma once
class Character : public Entity {
public:
	Character(Path txt_path, Area txt_area) : Entity(txt_path, txt_area){}
	~Character() {}
	virtual void onCollision(Entity* ent) override { 
		if (checkIfCollidesWithAnotherEntity(ent)) Console("Collission occured");
	}
	virtual void onCollisionWithGround(Ground* ground) override {
		if (checkIfCollidesWithGround(ground)) {
			this->setPosition(lastPosition);
		}
		else lastPosition = this->getSprite()->getPosition();
	}
	bool checkIfCollidesWithGround(Ground* ground) {
		return this->getBoudingBox()->intersects(ground->hitbox);
	}
	bool checkIfCollidesWithAnotherEntity(Entity* ent) {
		return this->getBoudingBox()->intersects(*ent->getBoudingBox());
	}
protected:
	mutable Health base_Health = 200;
	Health current_Health = base_Health;
	std::unordered_set<Component*> drawableComponents;
	std::unordered_set<Component*> importantComponents;
	Position lastPosition;
};
