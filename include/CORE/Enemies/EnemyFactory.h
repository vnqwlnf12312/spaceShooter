#include <memory>
#include <unordered_map>

#include "CORE/Enemies/Enemies.h"

#pragma once

class EnemyFactory {
 public:
  EnemyFactory(std::shared_ptr<BulletFactory> bullet_factory_);
  std::unique_ptr<EnemyPrototype> create(EnemyType type, Point position,
                                         std::shared_ptr<Move> movement);
  std::unique_ptr<EnemyPrototype> create(EnemyType type, Point position,
                                         std::shared_ptr<Move> movement,
                                         float speed,
                                         std::shared_ptr<Move> bullet_movement_,
                                         float bullet_speed);
  ~EnemyFactory() = default;

 private:
  std::unordered_map<EnemyType, std::unique_ptr<EnemyPrototype>> enemies;
  std::shared_ptr<BulletFactory> bullet_factory;
};
