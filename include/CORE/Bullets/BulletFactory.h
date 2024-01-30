#include <memory>
#include <unordered_map>

#include "CORE/Bullets/Bullets.h"
#pragma once

class BulletFactory {
 public:
  BulletFactory(std::shared_ptr<Move> default_movement);
  ~BulletFactory() = default;
  std::unique_ptr<BulletPrototype> create(BulletType type,
                                          const Point& position);
  std::unique_ptr<BulletPrototype> create(BulletType type,
                                          const Point& position,
                                          std::shared_ptr<Move> movement);
  std::unique_ptr<BulletPrototype> create(BulletType type,
                                          const Point& position,
                                          float bullet_speed);
  std::unique_ptr<BulletPrototype> create(BulletType type,
                                          const Point& position,
                                          std::shared_ptr<Move> movement,
                                          float bullet_speed);

  std::shared_ptr<Move> getDefaultMovement();

 private:
  std::unordered_map<BulletType, std::unique_ptr<BulletPrototype>,
                     std::hash<int> >
      prototypes_;
};
