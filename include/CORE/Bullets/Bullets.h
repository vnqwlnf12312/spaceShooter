#include <initializer_list>
#include <memory>

#include "CORE/Other/Condition.h"
#include "CORE/Other/Movement.h"

#pragma once

enum BulletType {
  SimpleBullet,
  TriangleBullet,
  BigCircleBullet,
  PercentDamageBullet
};

class BulletPrototype {
 public:
  virtual ~BulletPrototype(){};
  virtual std::unique_ptr<BulletPrototype> clone() const = 0;
  void update();

  void setSpeed(float new_speed);
  void setPosition(const Point& position);
  void setMovement(std::shared_ptr<Move> new_movement);
  void setDamage(float damage);
  Point getPosition();
  bool isOutOfBorder();
  BulletType getBulletType();
  std::shared_ptr<Move> getMovement();
  virtual float CalculateDamage(float hp) = 0;

  BulletType type;
  Condition cond;
  bool disappears_on_hero_hit;
  constexpr static std::initializer_list<BulletType> BulletTypeIter = {
      SimpleBullet, TriangleBullet, BigCircleBullet, PercentDamageBullet};

 protected:
  float damage;
  float speed;
  std::shared_ptr<Move> movement_type;
};

class BigCircleBullet : public BulletPrototype {
 public:
  BigCircleBullet(std::shared_ptr<Move> new_movement);
  BigCircleBullet(const BigCircleBullet& other);
  std::unique_ptr<BulletPrototype> clone() const override;
  float CalculateDamage(float hp) override;
};

class TriangleBullet : public BulletPrototype {
 public:
  TriangleBullet(std::shared_ptr<Move> new_movement);
  TriangleBullet(const TriangleBullet& other);
  std::unique_ptr<BulletPrototype> clone() const override;
  float CalculateDamage(float hp) override;
};

class PercentDamageBullet : public BulletPrototype {
 public:
  PercentDamageBullet(std::shared_ptr<Move> new_movement);
  PercentDamageBullet(const PercentDamageBullet& other);
  std::unique_ptr<BulletPrototype> clone() const override;
  float CalculateDamage(float hp) override;

 private:
  float percent;
};

class SimpleBullet : public BulletPrototype {
 public:
  SimpleBullet(std::shared_ptr<Move> new_movement);
  SimpleBullet(const SimpleBullet& other);
  std::unique_ptr<BulletPrototype> clone() const override;
  float CalculateDamage(float hp) override;
};
