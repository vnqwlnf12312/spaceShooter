//
// Created by Mac on 13.04.2023.
//

#include "GUI/Windows/levels.h"

#include <memory>
#include "GUI/Windows/chooseWindow.h"
#include "CORE/Other/future_config.h"

bool ReverseCmp::operator()(const sf::Time& first, const sf::Time& second) const {
  return first > second;
}

LevelWindow::LevelWindow(sf::RenderWindow& main_window, const std::shared_ptr<Player>& player, int level_selected) : painter(main_window, level_selected),
player(player) {
  setting(level_selected);
}

void LevelWindow::setting(int level_selected) {
  switch (level_selected) {
    case 0:
      level = std::make_unique<Level1>(player->getSelectedShip());
      break;
    case 1:
      level = std::make_unique<Level2>(player->getSelectedShip());
      break;
  }

  backgrounds[0] = Condition{0, 0, global_constants::SIZE.x, global_constants::SIZE.y, 0};
  backgrounds[1] = Condition{0, 0, global_constants::SIZE.x, global_constants::SIZE.y, 0};
  painter.setLevelWindowParameters();
}

Level::Level(ShipType ship_type) : bullet_factory(std::make_shared<BulletFactory>(std::make_shared<Linear>(0, -1))), enemy_factory(std::make_unique<EnemyFactory>(bullet_factory)) {
  switch (ship_type) {
    case ShipType::BasicShip:
      main_hero = std::make_unique<class BasicShip>(bullet_factory);
      break;
    case ShipType::TripleShotShip:
      main_hero = std::make_unique<class TripleShotShip>(bullet_factory);
      break;
  }
}

void Level1::setupLevel() {
  music.openFromFile(global_constants::src_dir + "/Music/level_music.ogg");
  clock.restart();
  music.play();
  previousTime = sf::seconds(0);
  is_alive = true;
}

Level1::Level1(ShipType ship_type) : Level(ship_type) {
  std::map<std::string, std::shared_ptr<Move>> directions;
  directions["U"] = std::make_shared<Linear>(0, -1);
  directions["R"] = std::make_shared<Linear>(1, 0);
  directions["D"] = std::make_shared<Linear>(0, 1);
  directions["L"] = std::make_shared<Linear>(-1, 0);
  directions["UR"] = std::make_shared<Linear>(1, -1);
  directions["RD"] = std::make_shared<Linear>(1, 1);
  directions["DL"] = std::make_shared<Linear>(-1, 1);
  directions["LU"] = std::make_shared<Linear>(-1, -1);
  enemies_to_spawn.insert(std::make_pair(sf::seconds(1), enemy_factory->create(ToughEnemyType, Point(200, 400),
                                                                               directions["U"], 0.5f, directions["D"], 1)));
  enemies_to_spawn.insert(std::make_pair(sf::seconds(2), enemy_factory->create(DefaultEnemyType, Point(200, 400),
                                                                               directions["UR"], 0.5f, directions["D"], 1)));
  enemies_to_spawn.insert(std::make_pair(sf::seconds(3), enemy_factory->create(DefaultEnemyType, Point(200, 400),
                                                                               directions["R"], 0.5f, directions["D"], 1)));
  enemies_to_spawn.insert(std::make_pair(sf::seconds(4), enemy_factory->create(DefaultEnemyType, Point(200, 400),
                                                                               directions["RD"], 0.5f, directions["D"], 1)));
  enemies_to_spawn.insert(std::make_pair(sf::seconds(5), enemy_factory->create(DefaultEnemyType, Point(200, 400),
                                                                               directions["D"], 0.5f, directions["D"], 1)));
  enemies_to_spawn.insert(std::make_pair(sf::seconds(6), enemy_factory->create(DefaultEnemyType, Point(200, 400),
                                                                               directions["DL"], 0.5f, directions["D"], 1)));
  enemies_to_spawn.insert(std::make_pair(sf::seconds(7), enemy_factory->create(DefaultEnemyType, Point(200, 400),
                                                                               directions["L"], 0.5f, directions["D"], 1)));
  enemies_to_spawn.insert(std::make_pair(sf::seconds(8), enemy_factory->create(ToughEnemyType, Point(200, 400),
                                                                               directions["LU"], 0.5f, directions["D"], 1)));
}

void LevelWindow::startLevel() {
  level->setupLevel();
}

void Level::draw(PainterLevelWindow& painter) {
  painter.drawLevel(main_hero, enemies, enemy_bullets, hero_bullets);
}

void Level::spawnEnemies() {
  sf::Time cur_time = clock.getElapsedTime();
  auto it = enemies_to_spawn.upper_bound(previousTime);
  if (it == enemies_to_spawn.begin()) {
    return;
  } else {
    --it;
  }
  while (it != enemies_to_spawn.end() && it->first <= cur_time) {
    enemies.push_back(std::move(it->second));
    if (it == enemies_to_spawn.begin()) {
      break;
    }
    --it;
  }
  previousTime = cur_time;
}

void Level::updateEnemies() {
  for (auto& enemy : enemies) {
    enemy->update();
    if (enemy->checkShoot()) {
      enemy_bullets.push_back(enemy->shoot());
    }
  }
}

void Level::popEnemies() {
  for (size_t i = 0; i < enemies.size();) {
    if (enemies[i]->isOutOfBorder()) {
      enemies.erase(enemies.begin() + i);
    } else {
      ++i;
    }
  }
}

void Level::popBullets() {
  for (size_t i = 0; i < enemy_bullets.size();) {
    if (enemy_bullets[i]->isOutOfBorder()) {
      enemy_bullets.erase(enemy_bullets.begin() + i);
    } else {
      ++i;
    }
  }
}

void Level::updateBullets() {
  for (auto& bullet : enemy_bullets) {
    bullet->update();
  }
  for (auto& bullet : hero_bullets) {
    bullet->update();
  }
  shootHero();
}

void Level::shootHero() {
  if (main_hero->checkShoot()) {
    for (auto& bullet : main_hero->shoot()) {
      hero_bullets.push_back(std::move(bullet));
    }
  }
}

void Level::update() {

  calculateDamage();

  popDeadEnemies();

  checkDeadHero();

  spawnEnemies();

  updateEnemies();

  popEnemies();

  updateBullets();

  shootHero();

  popBullets();

}

void Level::moveHeroLeft() {
  main_hero->moveLeft();
}

void LevelWindow::aPressed() {
  level->moveHeroLeft();
}

void Level::moveHeroRight() {
  main_hero->moveRight();
}

void LevelWindow::dPressed() {
  level->moveHeroRight();
}

void Level::moveHeroUp() {
  main_hero->moveUp();
}

void LevelWindow::wPressed() {
  level->moveHeroUp();
}

void Level::moveHeroDown() {
  main_hero->moveDown();
}

void LevelWindow::sPressed() {
  level->moveHeroDown();
}

void LevelWindow::updateWindow() {
  painter.setLevelWindowParameters();
  level->update();
  level->draw(painter);
}

Level2::Level2(ShipType ship_type) : Level(ship_type) {
//  enemies_to_spawn.insert(std::make_pair(sf::seconds(1), enemy_factory->create(DefaultEnemyType, Point(200, 400),
//                                                                               new Linear(0, -0.01), 0.01, 1)));
//  enemies_to_spawn.insert(std::make_pair(sf::seconds(1), enemy_factory->create(DefaultEnemyType, Point(200, 400),
//                                                                               new Linear(0.01, -0.01), 0.01, 1)));
//  enemies_to_spawn.insert(std::make_pair(sf::seconds(2), enemy_factory->create(DefaultEnemyType, Point(200, 400),
//                                                                               new Linear(0.01, 0), 0.01, 1)));
//  enemies_to_spawn.insert(std::make_pair(sf::seconds(3), enemy_factory->create(DefaultEnemyType, Point(200, 400),
//                                                                               new Linear(0.01, 0.01), 0.01, 1)));
//  enemies_to_spawn.insert(std::make_pair(sf::seconds(4), enemy_factory->create(DefaultEnemyType, Point(200, 400),
//                                                                              new Linear(0, 0.01), 0.01, 1)));
//  enemies_to_spawn.insert(std::make_pair(sf::seconds(5), enemy_factory->create(DefaultEnemyType, Point(200, 400),
//                                                                               new Linear(-0.01, 0.01), 0.01, 1)));
//  enemies_to_spawn.insert(std::make_pair(sf::seconds(6), enemy_factory->create(DefaultEnemyType, Point(200, 400),
//                                                                               new Linear(-0.01, 0), 0.01, 1)));
//  enemies_to_spawn.insert(std::make_pair(sf::seconds(7), enemy_factory->create(DefaultEnemyType, Point(200, 400),
//                                                                               new Linear(-0.01, -0.01), 0.01, 1)));
}

void Level2::setupLevel() {
  music.openFromFile(global_constants::src_dir + "/Music/VivaldiFonk.ogg");
  clock.restart();
  music.play();
  is_alive = true;
}

void Level::clearLevel() {
  music.stop();
}

Window* LevelWindow::escapePressed() {
  level->clearLevel();
  Window* to_return =  new ChooseWindow(painter.getWindow(), nullptr, player);
  to_return->loadMusic();
  return to_return;
}

void Level::calculateDamage() {
  bool hit = false;
  for (size_t i = 0; i < hero_bullets.size();) {
    hit = false;
    for (auto& enemy: enemies) {
      if (checkInterfere(hero_bullets[i]->cond, enemy->cond)) {
        enemy->takeDamage(hero_bullets[i]->CalculateDamage(enemy->getHP()));
        hero_bullets.erase(hero_bullets.begin() + i);
        break;
      }
    }
    if (!hit) {
      ++i;
    }
  }
  if (!main_hero->checkInvincible()) {
    for (size_t i = 0; i < enemy_bullets.size(); ++i) {
      if (checkInterfere(enemy_bullets[i]->cond, main_hero->cond)) {
        std::cout << "touched hero" << std::endl;
        main_hero->takeDamage(enemy_bullets[i]->CalculateDamage(main_hero->getHP()));
        main_hero->startInvincibility();
        if (enemy_bullets[i]->disappears_on_hero_hit) {
          enemy_bullets.erase(enemy_bullets.begin() + i);
        }
        break;
      }
    }
  }
}

void Level::popDeadEnemies() {
  for (size_t i = 0; i < enemies.size();) {
    if (enemies[i]->getHP() < 0) {
      enemies.erase(enemies.begin() + i);
    } else {
      ++i;
    }
  }
}

void Level::checkDeadHero() {
  if (main_hero->getHP() < 0) {
    std::cout << "hero is dead" << std::endl;
  }
}