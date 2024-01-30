#include "CORE/Hero/Hero.h"
#include <SFML/System/Time.hpp>
#include "CORE/Other/future_config.h"

#define BULLET_POSITION_X cond.x + cond.width / 2
#define BULLET_POSITION_Y cond.y - cond.height / 2

const float PlayerSpeed = 10;

void ShipPrototype::moveUp() {
  if (cond.y - PlayerSpeed > 0 && cooldown_move < clock_move_vert.getElapsedTime()) {
    clock_move_vert.restart();
    cond.y -= PlayerSpeed;
  }
}

void ShipPrototype::moveDown() {
  if (cond.y + cond.height + PlayerSpeed < global_constants::SIZE.y && cooldown_move < clock_move_vert.getElapsedTime()) {
    clock_move_vert.restart();
    cond.y += PlayerSpeed;
  }
}

void ShipPrototype::moveLeft() {
  if (cond.x - PlayerSpeed > 0 && cooldown_move < clock_move_hor.getElapsedTime()) {
    clock_move_hor.restart();
    cond.x -= PlayerSpeed;
  }
}

void ShipPrototype::moveRight() {
  if (cond.x + cond.width + PlayerSpeed < global_constants::SIZE.x && cooldown_move < clock_move_hor.getElapsedTime()) {
    clock_move_hor.restart();
    cond.x += PlayerSpeed;
  }
}

float ShipPrototype::getHP() const {
  return health;
}

bool ShipPrototype::checkShoot() {
  if (clock_shoot.getElapsedTime() > cooldown_shoot) {
    clock_shoot.restart();
    return true;
  }
  return false;
}

void ShipPrototype::changeCooldownMilliseconds(int new_cooldown) {
  cooldown_shoot = sf::milliseconds(new_cooldown);
}

ShipType ShipPrototype::getShipType() {
  return ship_type;
}

void ShipPrototype::setDefaults() {
  health = health_default;
  bullet_speed = bullet_speed_default;
  bullet_type = bullet_type_default;
}

bool ShipPrototype::checkInvincible() {
  return clock_invincibility.getElapsedTime() < cooldown_shooted_invincible;
}

void ShipPrototype::startInvincibility() {
  clock_invincibility.restart();
}

void ShipPrototype::takeDamage(float damage) {
  std::cout << "hero just took " << damage << std::endl;
  health -= damage;
}

// -----------------------------------------------------------------------------------------------------


BasicShip::BasicShip(std::shared_ptr<BulletFactory> fac) {
  cond = Condition(300, 300, 40, 40);
  ship_type = ShipType::BasicShip;
  bullet_factory = fac;

  health_default = 100.f;
  bullet_speed_default = 20.f;
  bullet_type_default = SimpleBullet;

  setDefaults();
}

std::list<std::unique_ptr<BulletPrototype>> BasicShip::shoot(BulletType type, std::shared_ptr<Move> movement, float speed) {
  std::list<std::unique_ptr<BulletPrototype>> answer;
  answer.push_back(bullet_factory->create(type, Point(BULLET_POSITION_X, BULLET_POSITION_Y), movement,
                              speed));
  return answer; // enjoying copy elision
}

std::list<std::unique_ptr<BulletPrototype>> BasicShip::shoot() {
  clock_shoot.restart();
  std::list<std::unique_ptr<BulletPrototype>> answer;
  answer.push_back(bullet_factory->create(bullet_type, Point(BULLET_POSITION_X, BULLET_POSITION_Y), bullet_speed));
  return answer;
}


// ------------------------------------------------------------------------------------------------------


TripleShotShip::TripleShotShip(std::shared_ptr<BulletFactory> fac) {
  cond = Condition(200, 200, 40, 40);
  ship_type = ShipType::TripleShotShip;
  bullet_factory = fac;
  bullet_movements = std::vector<std::shared_ptr<Move>>{std::make_shared<Linear>(-1, -5), std::make_shared<Linear>(0, -1), 
                                                        std::make_shared<Linear>(1, -5)};

  health_default = 100.f;
  bullet_speed_default = 20.f;
  bullet_type_default = TriangleBullet;

  setDefaults();
}

std::list<std::unique_ptr<BulletPrototype>> TripleShotShip::shoot(BulletType type, std::shared_ptr<Move> movement, float speed) {
  std::list<std::unique_ptr<BulletPrototype>> answer;
  answer.push_back(bullet_factory->create(type, Point(BULLET_POSITION_X, BULLET_POSITION_Y), bullet_movements[0],
                              speed));
  answer.push_back(bullet_factory->create(type, Point(BULLET_POSITION_X, BULLET_POSITION_Y), bullet_movements[1],
                              speed));
  answer.push_back(bullet_factory->create(type, Point(BULLET_POSITION_X, BULLET_POSITION_Y), bullet_movements[2],
                              speed));
  return answer; // enjoying copy elision
}

std::list<std::unique_ptr<BulletPrototype>> TripleShotShip::shoot() {
  std::list<std::unique_ptr<BulletPrototype>> answer;
  answer.push_back(bullet_factory->create(bullet_type, Point(BULLET_POSITION_X, BULLET_POSITION_Y), bullet_movements[0], bullet_speed));
  answer.push_back(bullet_factory->create(bullet_type, Point(BULLET_POSITION_X, BULLET_POSITION_Y), bullet_movements[1], bullet_speed));
  answer.push_back(bullet_factory->create(bullet_type, Point(BULLET_POSITION_X, BULLET_POSITION_Y), bullet_movements[2], bullet_speed));
  clock_shoot.restart();
  return answer;
}