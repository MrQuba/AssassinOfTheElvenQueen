#include <SFML/Graphics.hpp>
#include "../SFMLModifications/Texture.hpp"
#include "../Types/Types.hpp"
#pragma once

class Sprite : public sf::Sprite {
public:
	Sprite(Texture texture, Scale scale = Scale(1.f, 1.f)) {
		this->setTexture(*texture.getTexture());
		this->setScale(scale);
		boundingBox = this->getGlobalBounds();
	}
	sf::Sprite* getSprite() {
		return this;
	}
	BoundingBox* getBoundingBox() {
		return &this->boundingBox;
	}
	void move(Velocity velocity){
		sf::Sprite::move(velocity);
		boundingBox.left = this->getPosition().x;
		boundingBox.top = this->getPosition().y;
	}
private:
	BoundingBox boundingBox;
};
