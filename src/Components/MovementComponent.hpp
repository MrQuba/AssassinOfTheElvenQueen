#include "Component.hpp"
#include "../Types/Types.hpp"
#include "../Constants/EnviromentConstants.hpp"
#include <cstddef>
#include <concepts>
#include <functional>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#pragma once
template<class T = sf::Sprite>
class MovementComponent {
	typedef T* EntityPointer;
public: 
	MovementComponent(EntityPointer ptr) : entityPointer(ptr), isJumping(false) {}
	void move(Velocity* velocity) {
		jump(velocity->y);
		entityPointer->move(*velocity);
	}
	~MovementComponent() {}
	void jump(float& jumpVelocity) {
		if (isJumping) isFalling = true; 
		if (isFalling)jumpVelocity += ENVIROMENT::GRAVITY;  else { jumpVelocity = 0; }
		if (jumpVelocity > 5) jumpVelocity = 5;
	}
	bool canJump() { return !isJumping; }
	void setJumpVar(bool v) {
		isJumping = v;
	}
	void setIsFalling(bool b) { isFalling = b; }
private:
	bool isJumping;
	bool isFalling;
	EntityPointer entityPointer;
};