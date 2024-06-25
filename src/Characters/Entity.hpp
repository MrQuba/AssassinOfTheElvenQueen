#include <SFML/Graphics.hpp>
#include "../SFMLModifications/Texture.hpp"
#include "../SFMLModifications/Sprite.hpp"
#include "../Components/Component.hpp"
#include <unordered_set>
#pragma once
class Entity : public Texture, public Sprite {
public:
	Entity(Path txt_path, Area txt_area) : Texture(txt_path, txt_area), Sprite(static_cast<Texture&>(*this)){}
	virtual void update() = 0;
	~Entity() {}
	virtual void draw(sf::RenderWindow& window) = 0;
};