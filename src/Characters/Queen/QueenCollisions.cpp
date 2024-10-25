#include "Queen.hpp"

  void Queen::onCollision(Entity* ent){
    Character::onCollision(ent);
  }

	void Queen::onCollisionWithGround(Enviroment* enviroment){
    if (!checkIfCollidesWithGround(enviroment)) movement->isFalling = true; // && enviroment->type == (int)TYPE::ROOF
    else {
			movement->isFalling = false;
			switch (enviroment->type) {
				case (int)TYPE::GROUND:
					this->setPosition(this->getPosition().x, enviroment->getRectShape().getPosition().y - this->getBoundingBox()->height);
					Math<bool>::switchVarIfConditionMet((this->velocity.y > 0 && this->positive_velocity), this->positive_velocity);
					break;
				case (int)TYPE::ROOF:
					this->setPosition(this->getPosition().x, enviroment->getRectShape().getPosition().y + enviroment->getRectShape().getGlobalBounds().height);
					Math<bool>::switchVarIfConditionMet((this->velocity.y < 0 && !this->positive_velocity), this->positive_velocity);
					break;
				case (int)TYPE::WALL:
					float oldPosX = this->getPosition().x;
					if(oldPosX > SIZE::WorldWidth){
						collidedWithWall = 1;
						this->setPosition(enviroment->getRectShape().getPosition().x - this->getBoundingBox()->width, this->getPosition().y);
					}
					else if(oldPosX < SIZE::GroundHeight){
						collidedWithWall = 2;
						this->setPosition(enviroment->getRectShape().getPosition().x, this->getPosition().y);

					}
					break;
			}
		}
		
		if(this->getPosition().y < SIZE::GroundHeight) this->setPosition(this->getPosition().x, SIZE::GroundHeight);
		else if(this->getPosition().y > (SIZE::WindowHeight-SIZE::GroundHeight)+this->getGlobalBounds().height) this->setPosition(this->getPosition().x, (SIZE::WindowHeight-SIZE::GroundHeight)-this->getGlobalBounds().height);
	}  

