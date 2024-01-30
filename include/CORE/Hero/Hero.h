#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <initializer_list>
#include <iostream>
#include <list>
#include <vector>

#include "CORE/Bullets/BulletFactory.h"
#include "CORE/Other/Condition.h"

#pragma once

enum ShipType { BasicShip, TripleShotShip };

class ShipPrototype {
 public:
  constexpr static std::initializer_list<ShipType> ShipTypeIter = {
      BasicShip, TripleShotShip};

  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
  float getHP() const;
  bool checkShoot();
  void changeCooldownMilliseconds(int new_cooldown);
  ShipType getShipType();
  void setDefaults();

  void takeDamage(float damage);
  bool checkInvincible();
  void startInvincibility();

  virtual std::list<std::unique_ptr<BulletPrototype>> shoot() = 0;
  virtual std::list<std::unique_ptr<BulletPrototype>> shoot(
      BulletType type, std::shared_ptr<Move> movement,
      float speed) = 0;  // всегда стреляет одной пулей

  Condition cond;

  virtual ~ShipPrototype() = default;

 protected:
  float health_default;
  float bullet_speed_default;
  BulletType bullet_type_default;
  float shooted_invincibility_duration;

  ShipType ship_type;
  std::shared_ptr<BulletFactory> bullet_factory;
  float health;
  float bullet_speed;
  BulletType bullet_type;
  sf::Clock clock_shoot;
  sf::Clock clock_move_vert;
  sf::Clock clock_move_hor;
  sf::Clock clock_invincibility;
  sf::Time cooldown_shoot = sf::milliseconds(500);
  sf::Time cooldown_move = sf::milliseconds(10);
  sf::Time cooldown_shooted_invincible = sf::milliseconds(2000);
};

class BasicShip : public ShipPrototype {
 public:
  BasicShip(std::shared_ptr<BulletFactory> fac);

  std::list<std::unique_ptr<BulletPrototype>> shoot() override;
  std::list<std::unique_ptr<BulletPrototype>> shoot(
      BulletType type, std::shared_ptr<Move> movement, float speed) override;
};

class TripleShotShip : public ShipPrototype {
 public:
  TripleShotShip(std::shared_ptr<BulletFactory> fac);

  std::list<std::unique_ptr<BulletPrototype>> shoot() override;
  std::list<std::unique_ptr<BulletPrototype>> shoot(
      BulletType type, std::shared_ptr<Move> movement, float speed) override;

 private:
  std::vector<std::shared_ptr<Move>> bullet_movements;
};
