#include "NPC.hpp"
#include "../Components/MovementComponent.hpp"
#include "../Components/HealthComponent.hpp"
#pragma once

class Queen : public NPC {
public:

	Queen(Path txt_path, Area txt_area) : NPC(txt_path, txt_area),
		velocity(Velocity(0.f, 0.f)),
		movement(new MovementComponent<Queen>(this)),
		health(new HealthComponent(Size(current_Health, 16.f))) {
		// Constructor
			// Initializing variables:
		current_Health = 2000;
			// Adding components that can be drawn to the set
		drawableComponents.insert(health);
		// Adding components that should be updated always to the set
		importantComponents.insert(health);
		// Creating reference in health for variable representing current set
		health->createReference(&current_Health);
	}
	void AI() override {
		movement->move(&this->velocity);
	}
	virtual void onCollision(Entity* ent) override { Character::onCollision(ent); }
	virtual void onCollisionWithGround(Enviroment* enviroment) override {
		if (checkIfCollidesWithGround(enviroment) == false) movement->setIsFalling(true);
		else {
			movement->setIsFalling(false);
			switch (enviroment->type) {
			case (int)TYPE::GROUND:
				this->setPosition(this->getPosition().x, enviroment->getRectShape().getPosition().y - this->getBoudingBox()->height);
				break;
			case (int)TYPE::ROOF:
				this->setPosition(this->getPosition().x, enviroment->getRectShape().getPosition().y + enviroment->getRectShape().getGlobalBounds().height);
				break;
			case (int)TYPE::WALL:

				break;
			}
		}
	}
	void update() override {
		AI();
		for (Component* comp : importantComponents) {
			comp->update();
		}

	}
	void draw(sf::RenderWindow& window) override {
		window.draw(static_cast<sf::Sprite&>(*this));

		health->setPos(Position(0, window.getSize().y - this->getLocalBounds().height));
		for (Component* comp : drawableComponents) {
			comp->draw(window);
		}
	}
	~Queen() {
		delete health;
		delete movement;
	}
private:
	MovementComponent<Queen>* movement;
	HealthComponent* health;
	const Velocity speed;
	Velocity velocity;
};
