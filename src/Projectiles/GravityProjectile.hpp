#include "Projectile.hpp"
#include "../Constants/SizeConstants.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <ctime>
#pragma once
class GravityProjectile : public Projectile{
	public:
    GravityProjectile(Path txt_path, Area txt_area, sf::Color c, Position pos = Position(0,0), int ttl = 60) : Projectile(txt_path, txt_area, c, pos, ttl){
    this->setColor(c);
    srand(time(NULL));
    velocityX = ((rand()% 2 + 1 == 1)? -2.5 : 2.5);
  }
		void AI() override {
			this->move(Velocity(velocityX, 9.8f));
      if(this->getPosition().y + this->getBoundingBox()->height >= SIZE::WorldHeight-SIZE::GroundHeight) isDead = true;
		}
    const unsigned int bAttackCooldown = 10;
    unsigned int attackCooldown = 0;
	  void onCollision(Entity* ent) override { 
      if(attackCooldown == 0){
        attackCooldown = bAttackCooldown;
        ent->damage(5);
      }
      else {
        attackCooldown--;
      }
      isDead = true;
    }
    void kill() { delete this; }
	  void onCollisionWithGround(Enviroment* enviroment) override {
        //isDead = true;
    }
    void draw(sf::RenderWindow& window) override{
        window.draw(*this->getSprite());
  }
  private:
  float velocityX;
};
