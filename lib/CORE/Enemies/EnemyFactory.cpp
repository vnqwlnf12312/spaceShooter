#include "CORE/Enemies/EnemyFactory.h"

#include <memory>

EnemyFactory::EnemyFactory(std::shared_ptr<BulletFactory> bullet_factory_)
    : bullet_factory(bullet_factory_) {
  std::shared_ptr<Move> bul_movement = bullet_factory_->getDefaultMovement();
  enemies[EnemyType::DefaultEnemyType] =
      std::make_unique<DefaultEnemy>(bullet_factory, bul_movement);
  enemies[EnemyType::ToughEnemyType] =
      std::make_unique<ToughEnemy>(bullet_factory, bul_movement);
  enemies[EnemyType::InvincibleEnemyType] =
      std::make_unique<InvincibleEnemy>(bullet_factory, bul_movement);
  enemies[EnemyType::BossType] = std::make_unique<Boss>(bullet_factory, bul_movement);
}


std::unique_ptr<EnemyPrototype> EnemyFactory::create(EnemyType type, Point position,
                                     std::shared_ptr<Move> movement) {
  std::unique_ptr<EnemyPrototype> to_return = enemies[type]->clone();
  to_return->setMove(movement);
  to_return->setPosition(position);
  return to_return;
}

std::unique_ptr<EnemyPrototype> EnemyFactory::create(EnemyType type, Point position,
                                     std::shared_ptr<Move> movement,
                                     float speed,
                                     std::shared_ptr<Move> bullet_movement_, float bullet_speed) {
  std::unique_ptr<EnemyPrototype> to_return = create(type, position, movement);
  to_return->setSpeed(speed);
  to_return->setBulletMovement(bullet_movement_);
  to_return->setBulletSpeed(bullet_speed);
  return to_return;
}
