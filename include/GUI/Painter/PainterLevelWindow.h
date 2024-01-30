#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <map>

#include "CORE/Bullets/Bullets.h"
#include "CORE/Enemies/Enemies.h"
#include "CORE/Hero/Hero.h"
#include "GUI/Painter/Painter.h"

#pragma once

class PainterLevelWindow : public Painter {
 public:
  PainterLevelWindow(sf::RenderWindow& main_window, int choLevel);

  void setLevelWindowParameters();
  void changeLevel(int new_level);
  void drawLevel(std::unique_ptr<ShipPrototype>& player,
                 std::vector<std::unique_ptr<EnemyPrototype>>& enemies,
                 std::vector<std::unique_ptr<BulletPrototype>>& enemy_bullets,
                 std::vector<std::unique_ptr<BulletPrototype>>& hero_bullets);

  ~PainterLevelWindow();

 private:
  void drawBackground();

  void drawPlayer(std::unique_ptr<ShipPrototype>& player);

  void drawEnemy(std::unique_ptr<EnemyPrototype>& enemy);
  void drawBullet(std::unique_ptr<BulletPrototype>& bullet);

  bool levelWindowLoaded = false;
  int choosed_level;

  int level_count = 2;
  std::map<ShipType, sf::Sprite> ShipSprites;
  std::map<ShipType, sf::Texture> ShipTextures;
  std::map<BulletType, sf::Sprite> BulletSprites;
  std::map<EnemyType, sf::Sprite> EnemySprites;
  std::map<BulletType, sf::Texture> BulletTextures;
  std::map<EnemyType, sf::Texture> EnemyTextures;
  std::map<int, sf::Texture>
      LevelBackgroundTextures;  // можно сделать на векторе, но так для
                                // единообразия
  std::map<int, sf::Sprite> LevelBackgroundSprites;
};
