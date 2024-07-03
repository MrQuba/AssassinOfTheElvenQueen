#include <SFML/Graphics.hpp>
#include "../Types/Types.hpp"
#include "../Logging/Logger.hpp"
#pragma once

class Camera : public sf::View {
public:
	Camera(Point center, Size size) : sf::View(center, size) {}
	~Camera() = default;
	void update(sf::Sprite* sprite) {
		this->setCenter(sprite->getPosition().x + (sprite->getGlobalBounds().width / 2), sprite->getPosition().y + (sprite->getGlobalBounds().height / 2));
	}
};
