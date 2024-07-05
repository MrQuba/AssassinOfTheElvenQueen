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
	Entity(Path txt_path, Area txt_area, Position pos) : Texture(txt_path, txt_area), Sprite(static_cast<Texture&>(*this)) {
		this->setPosition(pos);
	}
	~Entity() {}
};