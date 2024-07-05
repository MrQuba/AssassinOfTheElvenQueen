#include <SFML/Graphics.hpp>
#include "../SFMLModifications/Texture.hpp"
#include "../Interfaces/Drawable.hpp"
#pragma once

enum class TYPE{
	GROUND = 0,
	ROOF = 1,
	WALL = 10
};
class Enviroment : public Texture, sf::RectangleShape, public Drawable {
public:
	Enviroment(Path txt_path, Area txt_area, Size ground_size, Type type, Position pos) : Texture(txt_path, txt_area), sf::RectangleShape(ground_size), type(type) {
		this->setTexture(static_cast<sf::Texture*>(this));
		this->setRepeated(true);
		this->setPosition(pos);
	}
	void update() override{
		hitbox.left = this->getPosition().x;
		hitbox.top = this->getPosition().y;
		hitbox.width = this->getRectShape().getSize().x;
		hitbox.height = this->getRectShape().getSize().y;
	}
	void draw(sf::RenderWindow& window) override {
		window.draw(this->getRectShape());
	}
	sf::RectangleShape getRectShape() { return static_cast<sf::RectangleShape>(*this); }
	BoundingBox hitbox;
	Type type;
protected:
};