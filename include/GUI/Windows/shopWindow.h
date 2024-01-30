//
// Created by Mac on 19.03.2023.
//

#ifndef PROJECT__SHOPWINDOW_H_
#define PROJECT__SHOPWINDOW_H_
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "CORE/Other/Condition.h"
#include "CORE/Other/future_config.h"
#include "CORE/Player/Player.h"
#include "GUI/Painter/PainterMainMenu.h"
#include "GUI/Painter/PainterShopWindow.h"
#include "GUI/Windows/window.h"
#include "memory"

#pragma once

class ShopWindow : public Window {
 public:
  ShopWindow(sf::RenderWindow& main_window, std::shared_ptr<sf::Music> music,
             const std::shared_ptr<Player>& player);
  void setting();

  void moveLeft() override;
  void moveRight() override;
  int shipPressed();
  Window* escapePressed() override;
  Window* mousePressed(Point& mouse_pos) override;
  Window* pickOption() override;
  void updateWindow() override;
  ~ShopWindow();

 private:
  ShipType cur_ship = ShipType::BasicShip;
  Condition ship;
  Condition shop_sprite;
  Condition switch_ship_left;
  Condition switch_ship_right;
  Condition balance_text;
  Condition balance;
  Condition buy;
  Condition price;
  Condition description;
  PainterShopWindow painter;
  std::shared_ptr<Player> player;
  std::shared_ptr<sf::Music> music;
};

#endif  // PROJECT__SHOPWINDOW_H_
