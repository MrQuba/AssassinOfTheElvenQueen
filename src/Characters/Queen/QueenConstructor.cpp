#include "Queen.hpp"
#include <random>

Queen::Queen(Path txt_path, Area txt_area, Player *target, Position pos)
    : NPC(txt_path, txt_area, pos), velocity(Velocity(0.f, 0.f)),
      player(target), movement(new MovementComponent<Queen>(this)),
      health(new HealthComponent(Size(current_Health, 16.f))),
      displayHealth(current_Health), rng(rand_dev()), distribution(1, 100) {
  // Adding components that can be drawn to the set
  current_Health = 3500;
  drawableComponents.insert(health);
  // Adding components that should be updated always to the set
  importantComponents.insert(health);
  // Creating reference in health for variable representing current health
  health->createReference(&displayHealth);

  this->setColor(sf::Color::Magenta);
  this->velocity.x = this->speed.x;
}
