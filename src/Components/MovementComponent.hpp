#include "../Characters/Entity.hpp"
#include "../Constants/EnviromentConstants.hpp"
#include "../Types/Types.hpp"
#include <SFML/Graphics.hpp>
#pragma once
template <class T = Entity> class MovementComponent {
  typedef T *EntityPointer;

public:
  MovementComponent(EntityPointer ptr)
      : entityPointer(ptr), isJumping(false), isFalling(true) {}
  void move(Velocity *velocity) {
    jump(velocity->y);
    if (isDashing) {
      entityPointer->invicible = true;
      velocity->x = ((velocity->x < 0) ? -1 : 1) * dashSpeed;
      if (dashClock.getElapsedTime() >= dashDuration) {
        isDashing = false;
        dashCooldownClock.restart();
      }
    }
    if (!isDashing)
      entityPointer->invicible = false;
    if (canDashAgain() && !canDash) {
      canDash = true;
    }
    velocity->x /= entityPointer->slow;
    entityPointer->move(*velocity);
  }
  ~MovementComponent() {}
  void jump(float &jumpVelocity) {
    if (isJumping)
      isFalling = true;
    if (isFalling)
      jumpVelocity += ENVIROMENT::GRAVITY;
    else {
      jumpVelocity = 0;
    }
    if (jumpVelocity > 5)
      jumpVelocity = 5;
  }
  bool canJump() { return !isJumping; }
  void setJumpVar(bool v) { isJumping = v; }
  void restartDashClock() { dashClock.restart(); }
  bool canDashAgain() {
    return dashCooldownClock.getElapsedTime() >= dashCooldownDuration;
  }
  bool canDash = true;
  bool isDashing = false;
  float dashSpeed = 12.f;
  sf::Clock dashClock;
  sf::Clock dashCooldownClock;
  const sf::Time dashCooldownDuration = sf::seconds(1.0f);
  const sf::Time dashDuration = sf::seconds(0.2f);
  bool isJumping;
  bool isFalling;
  EntityPointer entityPointer;
};
