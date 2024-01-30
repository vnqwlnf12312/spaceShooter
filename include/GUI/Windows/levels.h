//
// Created by Mac on 19.03.2023.
//

#ifndef PROJECT_HEADERS_LEVELS_H_
#define PROJECT_HEADERS_LEVELS_H_
#include <SFML/Audio.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

#include "CORE/Bullets/BulletFactory.h"
#include "CORE/Enemies/EnemyFactory.h"
#include "CORE/Hero/Hero.h"
#include "CORE/Other/Condition.h"
#include "CORE/Other/future_config.h"
#include "CORE/Player/Player.h"
#include "GUI/Painter/PainterLevelWindow.h"
#include "GUI/Windows/window.h"

#pragma once

struct ReverseCmp {
  bool operator()(const sf::Time& first, const sf::Time& second) const;
};

enum levels { first, second, third };

class Level {
 public:
  Level(ShipType ship_type);

  virtual void setupLevel() = 0;
  void clearLevel();

  void spawnEnemies();

  void updateEnemies();

  void popEnemies();

  void updateBullets();

  void popBullets();

  void shootHero();

  void calculateDamage();

  void popDeadEnemies();

  void checkDeadHero();

  void moveHeroLeft();
  void moveHeroUp();
  void moveHeroRight();
  void moveHeroDown();

  void draw(PainterLevelWindow& painter);

  void update();

  virtual ~Level() = default;

 protected:
  std::shared_ptr<BulletFactory> bullet_factory;
  std::unique_ptr<ShipPrototype> main_hero;
  std::unique_ptr<EnemyFactory> enemy_factory;
  std::multimap<sf::Time, std::unique_ptr<EnemyPrototype>, ReverseCmp>
      enemies_to_spawn;
  std::vector<std::unique_ptr<EnemyPrototype>> enemies;
  std::vector<std::unique_ptr<BulletPrototype>> enemy_bullets;
  std::vector<std::unique_ptr<BulletPrototype>> hero_bullets;
  sf::Music music;
  sf::Time previousTime;
  sf::Clock clock;
  std::shared_ptr<Player> player;
  bool is_alive;
};

class LevelWindow : public Window {
 public:
  LevelWindow(sf::RenderWindow& main_window,
              const std::shared_ptr<Player>& player, int level_selected);
  void setting(int level_selected);

  void startLevel();

  void wPressed() override;
  void aPressed() override;
  void sPressed() override;
  void dPressed() override;
  Window* escapePressed() override;
  void updateWindow() override;

  void update();

 private:
  Condition backgrounds[global_constants::amount_of_levels];
  std::unique_ptr<Level> level;
  PainterLevelWindow painter;
  std::shared_ptr<Player> player;
};

class Level1 : public Level {
 public:
  Level1(ShipType ship_type);
  void setupLevel() override;
};

class Level2 : public Level {
 public:
  Level2(ShipType ship_type);
  void setupLevel() override;
};

#endif  // PROJECT_HEADERS_LEVELS_H_
