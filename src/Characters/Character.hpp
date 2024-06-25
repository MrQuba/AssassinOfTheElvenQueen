#include "Entity.hpp"
#pragma once
class Character : public Entity {
public:
	Character(Path txt_path, Area txt_area) : Entity(txt_path, txt_area){}
	virtual void update() = 0;
	~Character() {}
	virtual void draw(sf::RenderWindow& window) = 0;
protected:
	mutable Health base_Health = 200;
	Health current_Health = base_Health;
	std::unordered_set<Component*> drawableComponents;
	std::unordered_set<Component*> importantComponents;
};
