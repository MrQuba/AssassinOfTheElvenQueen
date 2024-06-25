#include "Character.hpp"
#include "../Components/InputComponent.hpp"
#include "../Components/HealthComponent.hpp"
#pragma once

class Player : public Character {
public:
	Player(Path txt_path, Area txt_area) : Character(txt_path, txt_area),
		velocity(Velocity(0.f, 0.f)), 
		input(new InputComponent<Player>(Velocity(5.f, 25.f), &this->velocity, this)),
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
	// TODO, fix speed param

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
	~Player() {
		// TODO, fix this
		//delete input;
	}
private:
	InputComponent<Player>* input;
	HealthComponent* health;
	const Velocity speed = Velocity(5.f, 25.f);
	Velocity velocity;
};
