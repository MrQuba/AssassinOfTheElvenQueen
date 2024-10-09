#include "../../Components/HealthComponent.hpp"
#include "../../Components/MovementComponent.hpp"
#include "../../Constants/Paths.hpp"
#include "../../Math/Math.hpp"
#include "../../Projectiles/Arrow.hpp"
#include "../../Projectiles/GravityProjectile.hpp"
#include "../../Projectiles/Lasers.hpp"
#include "../../Projectiles/Projectile.hpp"
#include "../../Projectiles/Roots.hpp"
#include "../../Types/Types.hpp"
#include "../NPC.hpp"
#include "../Player.hpp"
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include <functional>
#include <list>
#include <random>
#include <utility>
#pragma once

template <class F, class... Args>
concept invocable = requires(F &&f, Args &&...args) {
  std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
};

class Queen : public NPC {
public:
  Queen(Path txt_path, Area txt_area, Player *target,
        Position pos = Position(0, 0));

  Player *player;
  Phase phase = 2;
  void AI() override; 
  std::list<Projectile *> projectiles;

  void onCollision(Entity *ent) override;
  void onCollisionWithGround(Enviroment *enviroment) override;

  void update() override {
    AI();
    displayHealth = current_Health * 0.25f;
    for (Component *comp : importantComponents) {
      comp->update();
    }
    if (projCooldown == 0) {
      projCooldown = bProjCooldown;
      for (auto it = projectiles.begin(); it != projectiles.end();) {
        if ((*it)->shouldBeKilled()) {
          (*it)->kill();
          it = projectiles.erase(it);
        } else {
          (*it)->update();
          if ((*it)->checkIfCollidesWithAnotherEntity(player))
            (*it)->onCollision(player);
          ++it;
        }
      }
    } else {
      projCooldown--;
    }
  }
  void draw(sf::RenderWindow &window) override;
  ~Queen() {
    delete health;
    delete movement;
    for (auto it = projectiles.begin(); it != projectiles.end();) {
      (*it)->kill();
      it = projectiles.erase(it);
    }
  }

private:
  short movementAmplitude = 6;
  short collidedWithWall = 0;

  bool positive_velocity = false;

  HealthComponent *health;
  Health displayHealth;

  const Velocity speed = Velocity(10.f, 5);
  Velocity velocity;
  MovementComponent<Queen> *movement;

  DefaultCooldown bGravProjCooldown = 1;
  Cooldown gravProjCooldown = 0;

  DefaultCooldown bRootCooldown = 240;
  Cooldown rootCooldown = 0;

  DefaultCooldown bProjCooldown = 1;
  Cooldown projCooldown = 0;

  DefaultCooldown bLaserCooldown = 240;
  Cooldown laserCooldown = bLaserCooldown;

  const int arrowAmount = 3;
  DefaultCooldown bArrowCooldown = 90;
  Cooldown arrowCooldown = bArrowCooldown;

  const int dashAmount = 5;
  int currentDashAmount = 0;
  DefaultCooldown bDashCooldown = 180;
  Cooldown dashCooldown = bDashCooldown;
  bool dashing = false;
  bool dashed = false;
  float oldVelocityX;

  template <class F, class... Args>
    requires invocable<F, Args...>
  void attackManager(const bool condition, F &&spawn, Cooldown &cooldown,
                     DefaultCooldown bCooldown, Args &&...args);

  void spawnLasers(int amount, int interval);
  void spawnHorizontalLasers(int amount, int interval);
  void spawnGravityProjectile();
  void spawnRoots();
  void spawnArrows();
  void spawnArrow(const Angle angle, const Position pos, const Velocity v);
  void spawnArrowBarrage(const int arrowAmount, const short dir);

  std::random_device rand_dev; // a seed source for the random number engine
  std::mt19937 rng;
  std::uniform_int_distribution<> distribution;

  void initVelocityX() {
    Math<float>::InvertVarIfConditionMet(
        (collidedWithWall == 1 && velocity.x > 0), this->velocity.x);
    Math<float>::InvertVarIfConditionMet(
        (collidedWithWall == 2 && velocity.x < 0), this->velocity.x);
  }
};
