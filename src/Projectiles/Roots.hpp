#include "Projectile.hpp"
#pragma  once

class Roots : public Projectile{
  public:
    Roots(Path txt_path, Area txt_area, sf::Color c, Position pos = Position(0,0), int ttl = 60) : Projectile(txt_path, txt_area, c, pos, ttl){
      this->setColor(c);
      this->setScale(10.f, 1.f);
  }
    const int bAttackCooldown = 30;
    int attackCooldown = 0;
		void AI() override {
		}
	  void onCollision(Entity* ent) override { 
      ent->slow = 3;
      ent->slow_time = 60;
      if(attackCooldown == 0){
          attackCooldown = bAttackCooldown;
          ent->damage(3);
      }
      else attackCooldown--;
    }

};
