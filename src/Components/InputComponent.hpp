#include "../Config/Config.hpp"
#include "../Constants/Paths.hpp"
#include "../Projectiles/Shuriken.hpp"
#include "Component.hpp"
#include "MovementComponent.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#pragma once

template <class T = sf::Sprite>
class InputComponent : public virtual Component {
public:
  InputComponent(const Velocity *speed, Velocity *velocityPointer, T *ent)
      : speed(speed), velocityPointer(velocityPointer),
        movement(new MovementComponent<T>(ent)),
        config(new Config::DataStructure), player(ent) {}
  void update() override {
    // reset velocity
    velocityPointer->x = 0.0f;
    // new velocity
    if (isKeyPressed(config->LEFT))
      velocityPointer->x -= speed->x;
    if (isKeyPressed(config->RIGHT))
      velocityPointer->x += speed->x;
    if (shurikenCooldown == 0) {
      shurikenCooldown = bShurikenCooldown;
      if (isKeyPressed(config->ATTACK)) {
        Position offset = Position(player->getPosition());

        player->win_ptr->setView(*(player->getView()));
        sf::Vector2f mousePos = player->win_ptr->mapPixelToCoords(
            sf::Mouse::getPosition(*(player->win_ptr)));
        sf::Vector2f direction(mousePos.x - offset.x, mousePos.y - offset.y);
        float baseAngle = std::atan2(direction.y, direction.x);
        float speed = 25.0f;

        float spread = 0.1f;

        for (int i = 0; i < 3; ++i) {
          float currentAngle = baseAngle + (i - 1) * spread;
          sf::Vector2f adjustedVelocity(std::cos(currentAngle) * speed,
                                        std::sin(currentAngle) * speed);
          player->proj.push_back(new Shuriken(
              PATH::playerTexture, Area(0, 0, 8, 8), sf::Color::Cyan,
              Position(player->getPosition()), 600, adjustedVelocity,
              currentAngle, Scale(2.f, 2.f)));

          offset.y += 1.5f * 8.f;
        }
      }
    } else
      shurikenCooldown--;
    if (isKeyPressed(config->JUMP) && movement->canJump()) {
      movement->setJumpVar(true);
      velocityPointer->y += -speed->y;
    }
    if (isKeyPressed(config->DASH) && movement->isDashing == false &&
        movement->canDash) {

      movement->isDashing = true;
      movement->canDash = false;
      movement->restartDashClock();
    }
    // move entity
    movement->move(velocityPointer);
  }
  void resetJump() { movement->isJumping = false; }
  void setIsFalling(bool b) { movement->isFalling = b; }
  Config::DataStructure *getConfig() { return config; }
  ~InputComponent() {
    delete movement;
    delete config;
  }
  void draw(sf::RenderWindow &window) override {}

private:
  bool isKeyPressed(Key key) { return sf::Keyboard::isKeyPressed(key); }
  Config::DataStructure *config;
  Velocity *velocityPointer;
  const Velocity *speed;
  MovementComponent<T> *movement;
  T *player;
  Cooldown shurikenCooldown = bShurikenCooldown;
  DefaultCooldown bShurikenCooldown = 30;
};
