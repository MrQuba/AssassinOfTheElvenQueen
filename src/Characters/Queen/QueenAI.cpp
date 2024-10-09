#include "Queen.hpp"
#include <utility>
void Queen::AI() {
  float oldPosX = this->getPosition().x;
  if (oldPosX >= 100)
    oldPosX /= 100;
  if (oldPosX >= 1000)
    oldPosX /= 100;
  initVelocityX();
  switch (phase) {
  case 0:
  case 1:
    velocity.y = Math<float>::CalculateFunctionValueForX(
        oldPosX, &std::cos, (float)movementAmplitude * oldPosX);

    attackManager((int)oldPosX % 3 == 0, &Queen::spawnGravityProjectile,
                  gravProjCooldown, bGravProjCooldown, this);
    attackManager(rootCooldown == 0, &Queen::spawnRoots, rootCooldown,
                  bRootCooldown, this);
    break;
  case 2:

    velocity.y = Math<float>::CalculateFunctionValueForX(
        oldPosX, &std::tan, (float)movementAmplitude); // calculate velocity
    velocity.y = std::atan(velocity.y);                // restrict velocity
    if (this->distribution(this->rng) <= 85)
      attackManager(laserCooldown == 0, &Queen::spawnLasers, laserCooldown,
                    bLaserCooldown, this, player->getView()->getSize().x / 16,
                    64);
    else
      attackManager(laserCooldown == 0, &Queen::spawnHorizontalLasers,
                    laserCooldown, bLaserCooldown, this,
                    player->getView()->getSize().y / 64, 64);
    attackManager(arrowCooldown == 0 && laserCooldown != 0, &Queen::spawnArrows,
                  arrowCooldown, bArrowCooldown, this);
    attackManager(
        dashCooldown == 0 || (!dashing && currentDashAmount > 0), [this]() { dashed = true; dashing = true; currentDashAmount--; }, dashCooldown, 99999);
    if (dashed == true) {
      dashed = false;
      oldVelocityX = this->velocity.x;
      velocity.x *= 8;
      const short dir =
          (player->getPosition().x - this->getPosition().x < 0) ? -1 : 1;
      attackManager(true, &Queen::spawnArrowBarrage, dashCooldown,
                    bDashCooldown, this, 5, dir);
    } else if (dashing == true && velocity.x > oldVelocityX) {
      const short dir = (velocity.x < 0) ? -1 : 1;
      velocity.x = (std::abs(velocity.x) - 4.f) * dir;
    } else if (dashing == true && velocity.x <= oldVelocityX) {
      velocity.x = oldVelocityX;
      dashing = false;
      dashCooldown = bDashCooldown;
    }
    break;
  }
   velocity.y = std::trunc(velocity.y * 100);
   velocity.y /= 100;
   if(positive_velocity){
      Math<float>::InvertVarIfConditionMet(velocity.y < 0, this->velocity.y);
   } 
   else {
      Math<float>::InvertVarIfConditionMet(velocity.y > 0, this->velocity.y);
   }
  movement->move(&velocity);

  if (this->getPosition().x + this->getBoundingBox()->width >=
      (player->getView()->getCenter().x +
       (player->getView()->getSize().x / 2) / 2))
    collidedWithWall = 1;
  if (this->getPosition().x <
      (player->getView()->getCenter().x - (player->getView()->getSize().x) / 3))
    collidedWithWall = 2;
}
void Queen::spawnLasers(int amount, int interval) {
  Angle angle = rand() % 3;
  const short dir = (rand() % 2 == 0) ? 1 : -1;
  angle *= dir;
  for (int i = 1; i <= amount; i++) {
    projectiles.push_back(new Lasers(
        PATH::playerTexture, Area(0, 0, 8, 8), angle,
        Scale(1.5f, (std::sin(angle)) * (135.f * (angle + dir))),
        Position(player->getView()->getCenter().x -
                     (player->getView()->getSize().x / 2) + (interval * i),
                 0.f),
        40));
  }
}
void Queen::spawnHorizontalLasers(int amount, int interval) {
  Console(amount);
  for (int i = 0; i <= amount; i++) {
    projectiles.push_back(
        new Lasers(PATH::playerTexture, Area(0, 0, 8, 8), 0,
                   Scale(SIZE::WorldWidth / 8.f, 1.5f),
                   Position(0.f, player->getView()->getCenter().y -
                                     (player->getView()->getSize().y / 2) +
                                     (interval * ((i == amount) ? 0 : i))),
                   40, true));
  }
}

void Queen::spawnGravityProjectile() {
  projectiles.push_back(new GravityProjectile(
      PATH::playerTexture, Area(0, 0, 8, 8), sf::Color::Green,
      Position(this->getPosition().x, this->getPosition().y), 600));
}
void Queen::spawnRoots() {
  projectiles.push_back(
      new Roots(PATH::playerTexture, Area(0, 0, 32, 32), sf::Color::Green,
                Position(player->getPosition().x - (player->getSize().x / 2.f),
                         SIZE::WorldHeight - SIZE::GroundHeight - 5)));
}
template <class F, class... Args>
  requires invocable<F, Args...>
void Queen::attackManager(const bool condition, F &&spawn, Cooldown &cooldown,
                          DefaultCooldown bCooldown, Args &&...args) {
  if (condition) {
    cooldown = bCooldown;
    std::invoke(std::forward<F>(spawn), std::forward<Args>(args)...);
  } else
    cooldown--;
}
void Queen::spawnArrows() {
  for (int i = 0; i < arrowAmount; i++) {
    Angle angle = (int)(this->distribution(this->rng) / 3);
    float slope = (std::tan(angle) * 100) / 100;
    short dir = ((this->distribution(this->rng) % 2 == 0) ? -1 : 1);
    slope *= dir;
    spawnArrow(angle, Position(player->getPosition().x, 2 * SIZE::GroundHeight),
               Velocity(slope, 3.5f * 9.8f));
  }
}
void Queen::spawnArrow(const Angle angle, const Position pos,
                       const Velocity v) {
  projectiles.push_back(new Arrow(PATH::playerTexture, Area(0, 0, 8, 32),
                                  sf::Color::Cyan, Position(pos), 600, v, angle,
                                  Scale(1.f, 2.5f)));
}
void Queen::spawnArrowBarrage(const int arrowAmount, const short dir) {
  for (int i = 0; i < arrowAmount; i++) {
    spawnArrow(
        -90 + (0.98f * -i * 3),
        Position(this->getPosition().x,
                 (this->getPosition().y + this->getBoundingBox()->height) +
                     (-24 * i)),
        Velocity(dir * 15.f, 0.098f * i));
  }
}
