#include "Component.hpp"
#include "MovementComponent.hpp"
#include "../Config/Config.hpp"
#include <iostream>
#pragma once

template<class T = sf::Sprite>
class InputComponent : public virtual Component {
public:
	InputComponent(const Velocity* speed, Velocity* velocityPointer, T* ent) : speed(speed), velocityPointer(velocityPointer), movement(new MovementComponent<T>(ent)), config(new Config::DataStructure){}
	void update() override {
		// reset velocity
		velocityPointer->x = 0.0f;
		// new velocity
		if (isKeyPressed(config->LEFT)) velocityPointer->x -= speed->x;
		if (isKeyPressed(config->RIGHT)) velocityPointer->x += speed->x;
		if (isKeyPressed(config->JUMP) && movement->canJump()) {
			movement->setJumpVar(true);
			velocityPointer->y += -speed->y;
		}
		//move entity
		movement->move(velocityPointer);
	}
	void resetJump(){
		movement->setJumpVar(false);
	}
	void setIsFalling(bool b) {
		movement->setIsFalling(b);
	}
	Config::DataStructure* getConfig() { return config; }
	~InputComponent() { 
		delete movement;
		delete config;
	}
	void draw (sf::RenderWindow& window) override {}
private:
	bool isKeyPressed(Key key) {
		return sf::Keyboard::isKeyPressed(key);
	}
	Config::DataStructure* config;
	Velocity* velocityPointer;
	const Velocity* speed;
	MovementComponent<T>* movement;
};
