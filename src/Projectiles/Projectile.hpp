#include <SFML/Graphics.hpp>
#include "../Characters/NPC.hpp"
#pragma once
class Projectile : public NPC{
	public:
    Projectile(Path txt_path, Area txt_area, sf::Color c, Position pos = Position(0,0), int ttl = 60) : NPC(txt_path, txt_area, pos), ttl(ttl), isDead(false){
       this->setColor(c);
     }
		void update() override {
			AI();
      this->getBoundingBox()->top = this->getPosition().y;
      this->getBoundingBox()->left = this->getPosition().x;
      this->getBoundingBox()->width = this->getSize().x * this->getScale().x;
      this->getBoundingBox()->height = this->getSize().y * this->getScale().y;
      if(ttl == 0) isDead = true; else ttl--;
		}
    int ttl;
    bool isDead;
    bool shouldBeKilled() { return (ttl <= 0 || isDead == true) ? true : false; } 
	  virtual void onCollision(Entity* ent) override { 
      Character::onCollision(ent); 
    }
    void kill() { delete this; }
	  virtual void onCollisionWithGround(Enviroment* enviroment) override {
       if(enviroment->type != (short)TYPE::BACKGROUNDWALL) isDead = true;
    }
    void draw(sf::RenderWindow& window) override{
        window.draw(*this->getSprite());
  }
};

