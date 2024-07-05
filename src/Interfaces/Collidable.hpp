#include <SFML/Graphics.hpp>
#pragma once
template <class T = sf::Sprite,
class U = sf::RectangleShape>
class Collidable {
public:
	virtual void onCollision(T* ent) = 0;
	virtual void onCollisionWithGround(U* Enviroment) = 0;
};