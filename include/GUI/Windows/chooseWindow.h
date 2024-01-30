//
// Created by Mac on 18.03.2023.
//

#ifndef PROJECT__CHOOSEWINDOW_H_
#define PROJECT__CHOOSEWINDOW_H_

#include "CORE/Player/Player.h"
#include "GUI/Painter/PainterChooseWindow.h"
#include "GUI/Painter/PainterLevelWindow.h"
#include "GUI/Painter/PainterMainMenu.h"
#include "GUI/Windows/levels.h"
#include "GUI/Windows/window.h"
#include "memory"

#pragma once

class ChooseWindow : public Window {
 public:
  ChooseWindow(sf::RenderWindow& main_window, std::shared_ptr<sf::Music> music,
               const std::shared_ptr<Player>& player);
  void setting();

  void loadMusic();

  void moveLeft() override;
  void moveRight() override;
  Window* escapePressed() override;
  Window* mousePressed(Point& mouse_pos) override;
  Window* pickOption() override;
  virtual void updateWindow() override;
  int levelPressed();
  ~ChooseWindow() = default;

 private:
  int level_selected = 0;
  Condition levels_sprites[global_constants::amount_of_levels];
  Condition choose_level_sprite;
  Condition switch_left_sprite;
  Condition switch_right_sprite;
  PainterChooseWindow painter;
  std::shared_ptr<Player> player;
  std::shared_ptr<sf::Music> music;
};

#endif  // PROJECT__CHOOSEWINDOW_H_
