#include "Character.hpp"
#include "../Components/InputComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Game/Camera.hpp"
#include "../Constants/SizeConstants.hpp"
#pragma once

class Player : public Character{
public:
	Player(Path txt_path, Area txt_area) : Character(txt_path, txt_area),
		speed(Velocity(5.f, 25.f)),
		velocity(Velocity(0.f, 0.f)),
		input(new InputComponent<Player>(&this->speed, &this->velocity, this)),
		health(new HealthComponent(Size(current_Health, 16.f))),
		camera(new Camera(Point(SIZE::WindowWidth / 2, SIZE::WindowHeight / 2), Size(SIZE::WindowWidth, SIZE::WindowHeight))) {
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
		camera->update(this->getSprite());
		health->setPos(
			Position(
			this->getView()->getCenter().x - (this->getView()->getSize().x / 2),
			this->getView()->getCenter().y - (this->getView()->getSize().y / 2)
		));
	}
	sf::View* getView() { return camera; }
	void draw(sf::RenderWindow& window) override {
		window.draw(static_cast<sf::Sprite&>(*this));

		for (Component* comp : drawableComponents) {
			comp->draw(window);
		}
	}

	virtual void onCollision(Entity* ent) override {Character::onCollision(ent);}
	virtual void onCollisionWithGround(Ground* ground) override {
		if (checkIfCollidesWithGround(ground) == false) input->setIsFalling(true);
		else {
			input->resetJump();
			input->setIsFalling(false);
		}
		Character::onCollisionWithGround(ground);
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
	Camera* camera;
};
