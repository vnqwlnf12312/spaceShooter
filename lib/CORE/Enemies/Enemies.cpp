#include "CORE/Enemies/Enemies.h"
#include "CORE/Other/future_config.h"

bool EnemyPrototype::isOutOfBorder() {
  return cond.x < 0 || cond.x + cond.width > global_constants::SIZE.x || cond.y > global_constants::SIZE.y ||
         cond.y + cond.height < 0;
}

float EnemyPrototype::getHP() { return health; }

EnemyType EnemyPrototype::getEnemyType() {
  return type;
}

void EnemyPrototype::setMove(std::shared_ptr<Move> other_movement) { movement = other_movement; }

void EnemyPrototype::setSpeed(float set_speed) { speed = set_speed; }

void EnemyPrototype::setBulletSpeed(float set_speed) { bullet_speed = set_speed; }

void EnemyPrototype::setBulletMovement(std::shared_ptr<Move> new_movement) { bullet_movement = new_movement; }

void EnemyPrototype::setPosition(Point position) { cond.setPosition(position); }

bool EnemyPrototype::checkShoot() {
  if (cooldown < clock.getElapsedTime()) {
    return true;
  }
  return false;
}

std::unique_ptr<BulletPrototype> EnemyPrototype::shoot() {
  clock.restart();
  return bullet_factory->create(
      bullet_type, Point(cond.x + cond.width / 4, cond.y + cond.height),
      bullet_movement, bullet_speed);
}

std::unique_ptr<BulletPrototype> EnemyPrototype::shoot(BulletType type, std::shared_ptr<Move> bullet_movement, float speed) {
  clock.restart();
  return bullet_factory->create(
      type, Point(cond.point().x + cond.width / 4, cond.y + cond.width / 2),
      bullet_movement, speed);
}

void EnemyPrototype::update() { cond.move(movement->move(cond.point(), speed)); }

Point EnemyPrototype::getPosition() { return cond.point(); }

void EnemyPrototype::takeDamage(float damage) { health -= damage; }

//----------------------

DefaultEnemy::DefaultEnemy(std::shared_ptr<BulletFactory> bullet_factory_, std::shared_ptr<Move> bullet_movement_) {
  bullet_factory = bullet_factory_;
  bullet_movement = bullet_movement_;
  health = 100;
  speed = 0.1;
  bullet_speed = 0.1;
  cooldown = sf::seconds(1);
  type = DefaultEnemyType;
  bullet_type = BigCircleBullet;
  cond.height = global_constants::SIZE.y / 20;
  cond.width = global_constants::SIZE.x / 20;
  clock.restart();
}

std::unique_ptr<EnemyPrototype> DefaultEnemy::clone() { return std::make_unique<class DefaultEnemy>(*this); }

DefaultEnemy::DefaultEnemy(const DefaultEnemy& other) {
  health = other.health;
  speed = other.speed;
  bullet_movement = other.bullet_movement;
  bullet_speed = other.bullet_speed;
  bullet_type = other.bullet_type;
  movement = other.movement;
  cooldown = other.cooldown;
  bullet_factory = other.bullet_factory;
  cond = other.cond;
  type = other.type;
  clock.restart();
}

void DefaultEnemy::takeDamage(float damage) {
  health -= damage;
}

//--------------------------------------

float ToughEnemy::getArmor() { return armor; }

ToughEnemy::ToughEnemy(std::shared_ptr<BulletFactory> bullet_factory_, std::shared_ptr<Move> bullet_movement_) {
  bullet_factory = bullet_factory_;
  bullet_movement = bullet_movement_;
  health = 250;
  armor = 0.2;
  speed = 0.5;
  bullet_speed = 0.1;
  bullet_type = PercentDamageBullet;
  type = ToughEnemyType;
  cooldown = sf::milliseconds(1000);
  cond.height = global_constants::SIZE.y / 20;
  cond.width = global_constants::SIZE.x / 20;
  clock.restart();
}

std::unique_ptr<EnemyPrototype> ToughEnemy::clone() { return std::make_unique<class ToughEnemy>(*this); }

void ToughEnemy::takeDamage(float damage) { health -= damage * (1 - armor); }

ToughEnemy::ToughEnemy(const ToughEnemy& other) {
  health = other.health;
  speed = other.speed;
  armor = other.armor;
  bullet_speed = other.bullet_speed;
  bullet_movement = other.bullet_movement;
  bullet_type = other.bullet_type;
  movement = other.movement;
  cooldown = other.cooldown;
  bullet_factory = other.bullet_factory;
  cond = other.cond;
  type = other.type;
  clock.restart();
}

//--------------------------------------------

InvincibleEnemy::InvincibleEnemy(std::shared_ptr<BulletFactory> bullet_factory_, std::shared_ptr<Move> bullet_movement_) {
  bullet_factory = bullet_factory_;
  bullet_movement = bullet_movement_;
  health = 1;
  speed = 0.5;
  bullet_speed = 0.1;
  bullet_type = TriangleBullet;
  type = InvincibleEnemyType;
  cooldown = sf::milliseconds(1000);
  cond.height = global_constants::SIZE.y / 20;
  cond.width = global_constants::SIZE.x / 20;
  clock.restart();
}

void InvincibleEnemy::takeDamage(float damage) {}

std::unique_ptr<EnemyPrototype> InvincibleEnemy::clone() { return std::make_unique<class InvincibleEnemy>(*this); }

InvincibleEnemy::InvincibleEnemy(const InvincibleEnemy& other) {
  health = other.health;
  speed = other.speed;
  movement = other.movement;
  bullet_speed = other.bullet_speed;
  bullet_type = other.bullet_type;
  bullet_movement = other.bullet_movement;
  bullet_factory = other.bullet_factory;
  cooldown = other.cooldown;
  cond = other.cond;
  type = other.type;
  clock.restart();
}

//-------------------------------------------

Boss::Boss(std::shared_ptr<BulletFactory> bullet_factory_, std::shared_ptr<Move> bullet_movement_) {
  bullet_factory = bullet_factory_;
  bullet_movement = bullet_movement_;
  health = 3000;
  speed = 0;
  bullet_speed = 0.1;
  bullet_type = PercentDamageBullet;
  type = BossType;
  cooldown = sf::milliseconds(1000);
  cond.height = global_constants::SIZE.y / 10;
  cond.width = global_constants::SIZE.x / 10;
  clock.restart();
}

std::unique_ptr<EnemyPrototype> Boss::clone() { return std::make_unique<class Boss>(*this); }

Boss::Boss(const Boss& other) {
  health = other.health;
  speed = other.speed;
  movement = other.movement;
  bullet_movement = other.bullet_movement;
  bullet_speed = other.bullet_speed;
  bullet_type = other.bullet_type;
  bullet_factory = other.bullet_factory;
  cooldown = other.cooldown;
  cond = other.cond;
  type = other.type;
  clock.restart();
}

void Boss::takeDamage(float damage) {
  health -= damage;
}