#include "Component.hpp"
#include "MovementComponent.hpp"
#include "../Config/Config.hpp"
#include <iostream>
#pragma once

template<class T = sf::Sprite>
class InputComponent : public Component {
public:
	InputComponent(Velocity speed, Velocity* velocityPointer, T* ent) : velocityPointer(velocityPointer), speed(speed), movement(new MovementComponent<T>(ent) ){}
	void update() override {
		// reset velocity
		velocityPointer->x = 0.0f;
		// new velocity
		if (isKeyPressed(config->LEFT)) velocityPointer->x -= speed.x;
		if (isKeyPressed(config->RIGHT)) velocityPointer->x += speed.x;
		if (isKeyPressed(config->JUMP) && movement->canJump()) {
			movement->setJumpVar(true);
			velocityPointer->y += -speed.y;
		}
		if (isKeyPressed(sf::Keyboard::Z)) resetJump();
		//move entity
		movement->move(velocityPointer);
	}
	void resetJump(){
		movement->setJumpVar(false);
	}
	Config::DataStructure* getConfig() { return config; }
	~InputComponent() { 
		delete movement;
		delete velocityPointer;
		//delete config;
	}
	void draw (sf::RenderWindow& window) override {}
private:
	bool isKeyPressed(Key key) {
		return sf::Keyboard::isKeyPressed(key);
	}
	Config::DataStructure* config = new Config::DataStructure;
	Velocity* velocityPointer;
	Velocity speed;
	MovementComponent<T>* movement;
};
