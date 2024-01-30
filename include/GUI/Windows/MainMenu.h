//
// Created by Mac on 17.03.2023.
//

#ifndef PROJECT__MAINMENU_H_
#define PROJECT__MAINMENU_H_
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Export.hpp>
#include <iostream>

#include "CORE/Other/future_config.h"
#include "CORE/Player/Player.h"
#include "GUI/Painter/PainterChooseWindow.h"
#include "GUI/Painter/PainterMainMenu.h"
#include "GUI/Painter/PainterShopWindow.h"
#include "GUI/Windows/window.h"
#include "SFML/Audio.hpp"

#pragma once

enum windows {
  chooseLevel,
  shop,
};

class MainMenu : public Window {
 public:
  MainMenu(sf::RenderWindow& main_window, std::shared_ptr<sf::Music> music,
           const std::shared_ptr<Player>& player = std::make_shared<Player>());
  void setting();

  void moveUp() override;
  void moveDown() override;
  Window* escapePressed() override;
  int mainPressed();
  void mouseContains(Point& mouse_pos) override;
  Window* mousePressed(Point& mouse_pos) override;
  Window* pickOption() override;
  void updateWindow() override;

  void loadMusic();

  ~MainMenu();

 private:
  int MainMenuSelected = -1;
  Condition unchosen_sprites[global_constants::menu_size];
  Condition chosen_sprites[global_constants::menu_size];
  Condition mainMenu[global_constants::menu_size];
  Condition main_menu_sprite;
  PainterMainMenu painter;
  std::shared_ptr<Player> player;
  std::shared_ptr<sf::Music> music;
};

#endif  // PROJECT__MAINMENU_H_
