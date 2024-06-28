#include <SFML/Graphics.hpp>
#include "../SFMLModifications/Texture.hpp"
#include "../Interfaces/Drawable.hpp"
#pragma once

class Ground : public Texture, sf::RectangleShape, public Drawable {
public:
	Ground(Path txt_path, Area txt_area, Size ground_size) : Texture(txt_path, txt_area), sf::RectangleShape(ground_size) {
		this->setTexture(static_cast<sf::Texture*>(this));
		this->setRepeated(true);
	}
	void update() override{
		hitbox.left = this->getPosition().x;
		hitbox.top = this->getPosition().y;
		hitbox.width = this->getRectShape().getSize().x;
		hitbox.height = this->getRectShape().getSize().y;
	}
	void draw(sf::RenderWindow& window) override {
		this->setPosition(0, window.getSize().y - (this->getLocalBounds().height));
		window.draw(this->getRectShape());
	}
	sf::RectangleShape getRectShape() { return static_cast<sf::RectangleShape>(*this); }
	BoundingBox hitbox;
protected:
};