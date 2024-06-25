
#pragma once
class Component {
public:
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
protected:
};