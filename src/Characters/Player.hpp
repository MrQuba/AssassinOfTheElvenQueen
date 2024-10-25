#include "Character.hpp"
#include "../Components/InputComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Game/Camera.hpp"
#include "../Constants/SizeConstants.hpp"
#include "../Projectiles/Projectile.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#pragma once
template<class B = NPC>
class Player : public Character{
public:
	Player(Path txt_path, Area txt_area, Position pos, sf::RenderWindow* wptr) : Character(txt_path, txt_area, pos),
		win_ptr(wptr),
		speed(Velocity(5.f, 30.f)),
		velocity(Velocity(0.f, 0.f)),
		input(new InputComponent<Player>(&this->speed, &this->velocity, this)),
		health(new HealthComponent(Size(current_Health, 16.f))),
		camera(new Camera(Point(SIZE::WindowWidth / 2.f, SIZE::WindowHeight / 2.f), Size(SIZE::WindowWidth, SIZE::WindowHeight))) {
			// Constructor
				// Adding components that can be drawn to the set
			drawableComponents.insert(health);
				// Adding components that should be updated always to the set
			importantComponents.insert(input);
			importantComponents.insert(health);
				// Creating reference in health for variable representing current health
			health->createReference(&current_Health);
	}

	void update() override {
		for (Component* comp : importantComponents) {
			comp->update();
		}
		if(projFrameSkip == bProjFrameSkip){
			projFrameSkip = 0;
			for (auto it = proj.begin(); it != proj.end();) {
        		if ((*it)->shouldBeKilled()) {
          			(*it)->kill();
          			it = proj.erase(it);
        		} else {
          			(*it)->update();
        		   if ((*it)->checkIfCollidesWithAnotherEntity(boss_ptr)){
           				(*it)->onCollision(boss_ptr);
				   }
          		++it;
        }
      }
	}
		else  
		 projFrameSkip++;
    if(slow_time > 0 ) slow_time--;
    else slow = 1;
		health->setPos(Position(camera->getView().getCenter().x - (camera->getView().getSize().x / 2),
			camera->getView().getCenter().y - (camera->getView().getSize().y / 2)));
		camera->update(*this->getSprite());

    if(resetCameraInterval == 0 && resetCameraRotation){
      resetCameraInterval = 3;
      camera->getView().setRotation(0);
    }
    else if(resetCameraRotation && resetCameraInterval != 0) 
      resetCameraInterval--;
	}
	sf::View* getView() { return &camera->getView(); }
	void draw(sf::RenderWindow& window) override {
		window.draw(static_cast<sf::Sprite&>(*this));

		for (Component* comp : drawableComponents) {
			comp->draw(window);
		}
		for(auto p : proj){
			p->draw(window);
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
				this->setPosition(this->getPosition().x, enviroment->getRectShape().getPosition().y - this->getBoundingBox()->height);
				break;
			case (int)TYPE::ROOF:
				this->setPosition(this->getPosition().x, enviroment->getRectShape().getPosition().y + enviroment->getRectShape().getGlobalBounds().height);
				break;
			case (int)TYPE::WALL:
				if(this->velocity.x < 0)
					this->setPosition(enviroment->getRectShape().getPosition().x + enviroment->getRectShape().getGlobalBounds().width, this->getPosition().y);
				else if(this->velocity.x > 0)
					this->setPosition(enviroment->getRectShape().getPosition().x - this->getBoundingBox()->width, this->getPosition().y);
				break;
			}
		}
	}
  void damage(int dmg) override{
    if(invicible) return;
    this->camera->getView().rotate((dmg > 4)? dmg / 4 : dmg / 2);
    this->current_Health -= dmg;
    resetCameraRotation = true;
  }
	~Player() {
		delete health;
		delete input;    
		delete boss_ptr;
		delete win_ptr;
	for (auto it = proj.begin(); it != proj.end();) {
      (*it)->kill();
      it = proj.erase(it);
    }
	}
	std::vector<Projectile*> proj;
	B* boss_ptr;
	sf::RenderWindow* win_ptr;
private:
	InputComponent<Player>* input;
	HealthComponent* health;
	const Velocity speed;
	Velocity velocity;
  bool resetCameraRotation = false;
  short resetCameraInterval = 3;
	Camera* camera;
	DefaultCooldown bProjFrameSkip = 1;
	Cooldown projFrameSkip = bProjFrameSkip;
};
