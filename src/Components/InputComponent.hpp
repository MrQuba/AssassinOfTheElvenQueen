#include "Component.hpp"
#include "MovementComponent.hpp"
#include "../Config/Config.hpp"
#include "../Constants/Paths.hpp"
#include "../Projectiles/Shuriken.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#pragma once

template<class T = sf::Sprite>
class InputComponent : public virtual Component {
public:
	InputComponent(const Velocity* speed, Velocity* velocityPointer, T* ent) : speed(speed), velocityPointer(velocityPointer), movement(new MovementComponent<T>(ent)), config(new Config::DataStructure), player(ent){}
	void update() override {
		// reset velocity
		velocityPointer->x = 0.0f;
		// new velocity
		if (isKeyPressed(config->LEFT)) velocityPointer->x -= speed->x;
		if (isKeyPressed(config->RIGHT)) velocityPointer->x += speed->x;
		if(shurikenCooldown == 0){
			shurikenCooldown = bShurikenCooldown;
			if (isKeyPressed(config->ATTACK)){
				Position offset = Position(player->getPosition());
				sf::Vector2i mouse = sf::Mouse::getPosition();
				sf::Vector2f direction(mouse.x - offset.x, mouse.y - offset.y);    
				float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    			direction /= magnitude; 
				float angle = std::atan(mouse.y/mouse.x);
				float modifier = 25.5f;
				float speed = 25;
				sf::Vector2f velocity(direction.x * speed, direction.y * speed);
					for(int i = 3; i > 0; i--){
						if(i == 2) modifier = 0.f;
						if(i == 1) modifier = -25.5f;
								 player->proj.push_back(
									 new Shuriken(PATH::playerTexture, Area(0, 0, 8, 8),
                                 	 sf::Color::Cyan, Position(offset), 600, velocity, angle+modifier,
                                  	 Scale(2.f, 2.f)));
									 offset.y += 1.5f * 8.f * 2.f;
					}
			}
		}
		else shurikenCooldown--;
		if (isKeyPressed(config->JUMP) && movement->canJump()) {
			movement->setJumpVar(true);
			velocityPointer->y += -speed->y;
		}
		if(isKeyPressed(config->DASH) && movement->isDashing == false && movement->canDash){

			movement->isDashing = true;
			movement->canDash = false;
			movement->restartDashClock();
		}
		//move entity
		movement->move(velocityPointer);
	}
	void resetJump(){
		movement->isJumping = false;
	}
	void setIsFalling(bool b) {
		movement->isFalling = b;
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
	T* player;
	Cooldown shurikenCooldown = bShurikenCooldown;
	DefaultCooldown bShurikenCooldown = 10;
};
