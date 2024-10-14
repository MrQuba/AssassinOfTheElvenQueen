#include "Projectile.hpp"
#include "../Types/Types.hpp"
#pragma once
class Lasers : public Projectile{
public:
  Lasers(
    Path txt_path, 
    Area txt_area,
    Angle angle = Angle(0.f),
    Scale scale = Scale(1.f,1.f),
    Position pos = Position(0,0), 
    int ttl = 240,
    bool horizontal = false) :
      Projectile(txt_path, txt_area, light, pos, ttl),
      finalScale(scale),
      startTTL(ttl),
      horizontal(horizontal){
      
      if(!this->horizontal)
      this->setScale(0.2f, scale.y);
      else this->setScale(scale.x, 0.2f);
      this->setRotation(angle);
    }
  
  void AI () override {
    if(darkeningColor){
      if(this->getColor().g > 111) 
        this->setColor(
          sf::Color(
            dark.r, 
            this->getColor().g - 8, 
            dark.b
          )
        );
      else if(this->getColor().g < 111) 
        darkeningColor = false;
    }
    else{
      if(this->getColor().g < 207) 
        this->setColor(
          sf::Color(
            light.r,
            this->getColor().g + 8,
            light.b
          )
        );
      else if (this->getColor().g > 207) darkeningColor = true;
    }
    if(!fullyAppeared){
      if(!horizontal){
        this->setScale(this->getScale().x + 0.05, this->getScale().y);
        if(this->getScale().x >= finalScale.x){
          fullyAppeared = true;
          ttl = startTTL;
        }
      }
      else {
        this->setScale(this->getScale().x, this->getScale().y + 0.05);
        if(this->getScale().y >= finalScale.y){
          fullyAppeared = true;
          ttl = startTTL;
        }
      }
    }

  }
  void onCollision(Entity* ent) override {
    if(damageCooldown == 0){ 
      damageCooldown = bDamageCoooldown;
      ent->damage(7);
    }
    else
      damageCooldown--;
  }
  
  private:
  DefaultCooldown colorChangeCooldown = 4;
  DefaultCooldown bDamageCoooldown = 30;
  Cooldown damageCooldown = 0;
  bool darkeningColor = true;
  const sf::Color dark = sf::Color(3, 111, 252);
  const sf::Color light =sf::Color(3, 207, 252);
  
  bool fullyAppeared = false;
  bool horizontal;
  Scale finalScale;
  int startTTL;
};
