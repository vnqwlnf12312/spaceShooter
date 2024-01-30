#include "CORE/Bullets/BulletFactory.h"

#include <memory>

BulletFactory::BulletFactory(std::shared_ptr<Move> default_movement) {
  prototypes_[BulletType::SimpleBullet] =
      std::make_unique<class SimpleBullet>(default_movement);
  prototypes_[BulletType::BigCircleBullet] =
      std::make_unique<class BigCircleBullet>(default_movement);
  prototypes_[BulletType::PercentDamageBullet] =
      std::make_unique<class PercentDamageBullet>(default_movement);
  prototypes_[BulletType::TriangleBullet] =
      std::make_unique<class TriangleBullet>(default_movement);
}

std::unique_ptr<BulletPrototype> BulletFactory::create(BulletType type,
                                                       const Point& position) {
  std::unique_ptr<BulletPrototype> answer = prototypes_[type]->clone();
  answer->setPosition(position);
  return answer;
}

std::unique_ptr<BulletPrototype> BulletFactory::create(BulletType type,
                                                       const Point& position, 
                                                       float bullet_speed) {
  std::unique_ptr<BulletPrototype> answer = prototypes_[type]->clone();
  answer->setPosition(position);
  answer->setSpeed(bullet_speed);
  return answer;
}

std::unique_ptr<BulletPrototype> BulletFactory::create(
    BulletType type, const Point& position, std::shared_ptr<Move> movement) {
  std::unique_ptr<BulletPrototype> answer = prototypes_[type]->clone();
  answer->setPosition(position);
  prototypes_[type]->setMovement(movement);
  return answer;
}

std::unique_ptr<BulletPrototype> BulletFactory::create(
    BulletType type, const Point& position, std::shared_ptr<Move> movement,
    float bullet_speed) {
  std::unique_ptr<BulletPrototype> answer = prototypes_[type]->clone();
  answer->setPosition(position);
  answer->setMovement(movement);
  answer->setSpeed(bullet_speed);
  return answer;
}

std::shared_ptr<Move> BulletFactory::getDefaultMovement() {
  return prototypes_[BulletType::SimpleBullet]->getMovement();
}

