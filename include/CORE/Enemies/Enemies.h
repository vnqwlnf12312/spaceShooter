#include <SFML/System.hpp>
#include <initializer_list>
#include <iostream>
#include <memory>

#include "CORE/Bullets/BulletFactory.h"
#include "CORE/Other/Movement.h"

#pragma once

enum EnemyType {
  DefaultEnemyType,
  ToughEnemyType,
  InvincibleEnemyType,
  BossType
};

class EnemyPrototype {
 protected:
  float health;
  float speed;
  float bullet_speed;
  sf::Time cooldown = sf::milliseconds(1000);
  sf::Clock clock;
  std::shared_ptr<Move> movement;
  std::shared_ptr<Move> bullet_movement;
  EnemyType type;

  std::shared_ptr<BulletFactory> bullet_factory;
  BulletType bullet_type;

 public:
  EnemyPrototype() = default;
  float getHP();
  void setMove(std::shared_ptr<Move> other_movement);
  void setSpeed(float set_speed);
  void setBulletSpeed(float set_speed);
  void setPosition(Point position);
  void setBulletMovement(std::shared_ptr<Move> new_movement);
  virtual std::unique_ptr<EnemyPrototype> clone() = 0;
  bool checkShoot();
  virtual std::unique_ptr<BulletPrototype> shoot();
  virtual std::unique_ptr<BulletPrototype> shoot(BulletType type,
                                                 std::shared_ptr<Move> movement,
                                                 float cur_speed);
  void update();
  Point getPosition();
  EnemyType getEnemyType();
  virtual void takeDamage(float damage) = 0;
  bool isOutOfBorder();
  virtual ~EnemyPrototype() = default;

  constexpr static std::initializer_list<EnemyType> EnemyTypeIter = {
      DefaultEnemyType, ToughEnemyType
      //,InvincibleEnemyType,
      // BossType
  };

  Condition cond;
};

class DefaultEnemy : public EnemyPrototype {
 public:
  std::unique_ptr<EnemyPrototype> clone() override;
  DefaultEnemy(const DefaultEnemy& other);
  DefaultEnemy(std::shared_ptr<BulletFactory> bullet_factory_,
               std::shared_ptr<Move> bullet_movement_);
  void takeDamage(float damage) override;
};

class ToughEnemy : public EnemyPrototype {
 public:
  ToughEnemy(std::shared_ptr<BulletFactory> bullet_factory_,
             std::shared_ptr<Move> bullet_movement_);
  ToughEnemy(const ToughEnemy& other);
  std::unique_ptr<EnemyPrototype> clone() override;
  float getArmor();
  void takeDamage(float damage) override;

 private:
  float armor;
};

class InvincibleEnemy : public EnemyPrototype {
 public:
  InvincibleEnemy(std::shared_ptr<BulletFactory> bullet_factory_,
                  std::shared_ptr<Move> bullet_movement_);
  InvincibleEnemy(const InvincibleEnemy& other);
  std::unique_ptr<EnemyPrototype> clone() override;
  void takeDamage(float damage) override;
};

class Boss : public EnemyPrototype {
 public:
  Boss(std::shared_ptr<BulletFactory> bullet_factory_,
       std::shared_ptr<Move> bullet_movement_);
  Boss(const Boss& other);
  void takeDamage(float damage) override;
  std::unique_ptr<EnemyPrototype> clone() override;
};
