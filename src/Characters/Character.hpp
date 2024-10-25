
#include "Entity.hpp"
#pragma once
class Character : public Entity {
public:
  Character(Path txt_path, Area txt_area) : Entity(txt_path, txt_area) {}
  Character(Path txt_path, Area txt_area, Position pos, Health health = 200)
      : Entity(txt_path, txt_area, pos, health) {}
  ~Character() {}
  virtual void onCollision(Entity *ent) override {
    // if (checkIfCollidesWithAnotherEntity(ent));
  }
  bool checkIfCollidesWithGround(Enviroment *Enviroment) {
    return this->getBoundingBox()->intersects(Enviroment->hitbox);
  }
  bool checkIfCollidesWithAnotherEntity(Entity *ent) {
    BoundingBox hitbox = *(this->getBoundingBox());
    hitbox.width *= this->getScale().x;
    hitbox.height *= this->getScale().y;
    return hitbox.intersects(*(ent->getBoundingBox()));
  }

protected:
  std::unordered_set<Component *> drawableComponents;
  std::unordered_set<Component *> importantComponents;
};
