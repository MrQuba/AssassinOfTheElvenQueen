#include <SFML/Graphics.hpp>
#pragma once
class Drawable {
public:
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual ~Drawable() = default;
};