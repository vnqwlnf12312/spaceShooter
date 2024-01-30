#include "CORE/Bullets/Bullets.h"
#include "CORE/Other/future_config.h"
#include <memory>

bool BulletPrototype::isOutOfBorder() {
  return cond.x < 0 || cond.x + cond.width > global_constants::SIZE.x || cond.y > global_constants::SIZE.y ||
     cond.y + cond.height < 0;
}

void BulletPrototype::update() {
  Point need = movement_type->move(cond.point(), speed);
  cond.setRotation(std::atan2(need.x, need.y) * 180.f / (std::atan(1) * 4));
  cond.move(need);
}

void BulletPrototype::setSpeed(float new_speed) {
  speed = new_speed;
}

void BulletPrototype::setMovement(std::shared_ptr<Move> new_movement) {
  movement_type = new_movement;
}

void BulletPrototype::setDamage(float new_damage) {
  damage = new_damage;
}

void BulletPrototype::setPosition(const Point& new_position) {
  cond.setPosition(new_position);
}

Point BulletPrototype::getPosition() {
  return cond.point();
}

std::shared_ptr<Move> BulletPrototype::getMovement() {
  return movement_type;
}

std::unique_ptr<BulletPrototype> BigCircleBullet::clone() const {
  return std::make_unique<BigCircleBullet>(*this);
}

float BigCircleBullet::CalculateDamage(float hp) {
  return damage;
}
 
BigCircleBullet::BigCircleBullet(std::shared_ptr<Move> new_movement) { 
  movement_type = new_movement;
  damage = 25.f;
  speed = 30.f;
  cond.width = global_constants::SIZE.x / 40;
  cond.height = global_constants::SIZE.y / 30;
  disappears_on_hero_hit = false;
  type = BulletType::BigCircleBullet;
}

BigCircleBullet::BigCircleBullet(const BigCircleBullet& other) {
  disappears_on_hero_hit = false;
  type = other.type;
  speed = other.speed;
  movement_type = other.movement_type;
  damage = other.damage;
  cond = other.cond;
}

TriangleBullet::TriangleBullet(std::shared_ptr<Move> new_movement) {
  disappears_on_hero_hit = false;
  movement_type = new_movement;
  damage = 15.f;
  speed = 30.f;
  cond.width = global_constants::SIZE.x / 40;
  cond.height = global_constants::SIZE.y / 40;
  type = BulletType::TriangleBullet;
}

TriangleBullet::TriangleBullet(const TriangleBullet& other) {
  disappears_on_hero_hit = false;
  type = other.type;
  speed = other.speed;
  movement_type = other.movement_type;
  cond = other.cond;
  damage = other.damage;
}

std::unique_ptr<BulletPrototype> TriangleBullet::clone() const {
  return std::make_unique<TriangleBullet>(*this);
}

float TriangleBullet::CalculateDamage(float hp) {
  return damage;
}

PercentDamageBullet::PercentDamageBullet(std::shared_ptr<Move> new_movement) {
  disappears_on_hero_hit = true;
  movement_type = new_movement;
  percent = 0.5f;
  speed = 30.f;
  cond.width = global_constants::SIZE.x / 150;
  cond.height = global_constants::SIZE.y / 30;
  type = BulletType::PercentDamageBullet;
}

PercentDamageBullet::PercentDamageBullet(const PercentDamageBullet& other) {
  disappears_on_hero_hit = true;
  type = other.type;
  speed = other.speed;
  movement_type = other.movement_type;
  percent = other.percent;
  cond = other.cond;
  damage = other.damage;
}

std::unique_ptr<BulletPrototype> PercentDamageBullet::clone() const {
  return std::make_unique<PercentDamageBullet>(*this);
}

float PercentDamageBullet::CalculateDamage(float hp) {
  return hp * percent;
}

SimpleBullet::SimpleBullet(std::shared_ptr<Move> new_movement) {
  disappears_on_hero_hit = true;
  movement_type = new_movement;
  damage = 5;
  speed = 40.f;
  cond.width = global_constants::SIZE.x / 150;
  cond.height = global_constants::SIZE.y / 30;
  type = BulletType::SimpleBullet;
}

SimpleBullet::SimpleBullet(const SimpleBullet& other) {
  disappears_on_hero_hit = true;
  type = other.type;
  speed = other.speed;
  movement_type = other.movement_type;
  cond = other.cond;
  damage = other.damage;
}

float SimpleBullet::CalculateDamage(float hp) {
  return damage;
}

std::unique_ptr<BulletPrototype> SimpleBullet::clone() const {
  return std::make_unique<SimpleBullet>(*this);
}

BulletType BulletPrototype::getBulletType() {
  return type;
}
