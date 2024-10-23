#include "Projectile.hpp"
#include "../Constants/SizeConstants.hpp"
class Shuriken : public Projectile{
 public:
    Shuriken(Path txt_path, Area txt_area, sf::Color c, Position pos = Position(0,0), int ttl = 60, Velocity v = Velocity(0, 0), Angle angle = 0.f, Scale scale = Scale(1.f, 1.f))
    : Projectile(txt_path, txt_area, c, pos, ttl),
    velocity(v){
      this->setColor(c);
      this->setScale(scale);
      this->setRotation(angle);
  }
		void AI() override {
			this->move(velocity);
      if(this->getPosition().y <= SIZE::GroundHeight) isDead = true;
		}
	  void onCollision(Entity* ent) override { 
        ent->damage(20);
        this->isDead = true;
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
