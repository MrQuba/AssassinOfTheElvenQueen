#include "Character.hpp"
#include "../Components/InputComponent.hpp"
#include "../Components/HealthComponent.hpp"
#pragma once

class Player : public Character{
public:
	Player(Path txt_path, Area txt_area, Position pos) : Character(txt_path, txt_area, pos),
		speed(Velocity(5.f, 25.f)),
		velocity(Velocity(0.f, 0.f)),
		input(new InputComponent<Player>(&this->speed, &this->velocity, this)),
		health(new HealthComponent(Size(current_Health, 16.f))){
			// Constructor
				// Adding components that can be drawn to the set
			drawableComponents.insert(health);
				// Adding components that should be updated always to the set
			importantComponents.insert(input);
			importantComponents.insert(health);
				// Creating reference in health for variable representing current set
			health->createReference(&current_Health);
	}

	void update() override {
		for (Component* comp : importantComponents) {
			comp->update();
		}

	}
	
	void draw(sf::RenderWindow& window) override {
		window.draw(static_cast<sf::Sprite&>(*this));

		for (Component* comp : drawableComponents) {
			comp->draw(window);
		}
	}

	virtual void onCollision(Entity* ent) override {Character::onCollision(ent);}
	virtual void onCollisionWithGround(Enviroment* enviroment) override {
		if (checkIfCollidesWithGround(enviroment) == false) input->setIsFalling(true);
		else {
			switch (enviroment->type) {
			case (int)TYPE::GROUND:
				input->resetJump();
				input->setIsFalling(false);
				this->setPosition(this->getPosition().x, enviroment->getRectShape().getPosition().y - this->getBoudingBox()->height);
				break;
			case (int)TYPE::ROOF:
				this->setPosition(this->getPosition().x, enviroment->getRectShape().getPosition().y + enviroment->getRectShape().getGlobalBounds().height);
				break;
			case (int)TYPE::WALL:
				if(this->velocity.x < 0)
					this->setPosition(enviroment->getRectShape().getPosition().x + enviroment->getRectShape().getGlobalBounds().width, this->getPosition().y);
				else if(this->velocity.x > 0)
					this->setPosition(enviroment->getRectShape().getPosition().x - this->getBoudingBox()->width, this->getPosition().y);
				break;
			}
		}
	}
	~Player() {
		delete health;
		delete input;
	}
private:
	InputComponent<Player>* input;
	HealthComponent* health;
	const Velocity speed;
	Velocity velocity;
};
