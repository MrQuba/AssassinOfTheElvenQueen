#include "Projectile.hpp"
#include "../Constants/SizeConstants.hpp"
class Arrow : public Projectile{
 public:
    Arrow(Path txt_path, Area txt_area, sf::Color c, Position pos = Position(0,0), int ttl = 60, Velocity v = Velocity(0, 0), Angle angle = 0.f, Scale scale = Scale(1.f, 1.f))
    : Projectile(txt_path, txt_area, c, pos, ttl),
    velocity(v){
      this->setColor(c);
      this->setScale(scale);
      this->setRotation(angle);
  }
		void AI() override {
			this->move(velocity);
      if(this->getPosition().y + this->getBoundingBox()->height >= SIZE::WorldHeight-SIZE::GroundHeight) isDead = true;
		}
    const unsigned int bAttackCooldown = 10;
    unsigned int attackCooldown = 0;
	  void onCollision(Entity* ent) override { 
      if(attackCooldown == 0){
        attackCooldown = bAttackCooldown;
        ent->damage(8);
      }
      else {
        attackCooldown--;
      }
      isDead = true;
    }
    void kill() { delete this; }
	  void onCollisionWithGround(Enviroment* enviroment) override {
        isDead = true;
    }
    void draw(sf::RenderWindow& window) override{
        window.draw(*this->getSprite());
  }
  private:
  Velocity velocity;

};
