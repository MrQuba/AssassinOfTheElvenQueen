#include <SFML/Graphics.hpp>
#include "../SFMLModifications/Texture.hpp"
#include "../SFMLModifications/Sprite.hpp"
#include "../Components/Component.hpp"
#include "../Interfaces/Drawable.hpp"
#include "../Interfaces/Collidable.hpp"
#include "../Enviroment/Enviroment.hpp"
#include <unordered_set>
#pragma once
class Entity : public Texture, public Sprite, public Drawable, public Collidable<Entity, Enviroment> {
public:
	Entity(Path txt_path, Area txt_area) : Texture(txt_path, txt_area), Sprite(static_cast<Texture&>(*this)){}
	Entity(Path txt_path, Area txt_area, Position pos, Health health = 200) : 
    Texture(txt_path, txt_area), 
    Sprite(static_cast<Texture&>(*this)),
    current_Health(health){
		  this->setPosition(pos);
	}
  virtual void damage(int dmg){}
  short slow = 1;
  int slow_time = 0;
	Health current_Health;
  bool invicible = false;
	~Entity() {}
};
