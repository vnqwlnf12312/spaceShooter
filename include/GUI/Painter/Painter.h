//
// Created by Mac on 02.05.2023.
//

#ifndef SPACERETARDS_INCLUDE_GUI_PAINTER_PAINTER_H_
#define SPACERETARDS_INCLUDE_GUI_PAINTER_PAINTER_H_

#include <SFML/Graphics.hpp>

#include "CORE/Other/Condition.h"

#pragma once

class Painter {
 protected:
  sf::RenderWindow& main_window;

 public:
  Painter(sf::RenderWindow& main_window);
  sf::RenderWindow& getWindow();
  void exit();
  void fixSprite(sf::Sprite& sprite, const Condition& cond);
  void fixText(sf::Text& text, const Condition& cond);
  void display();
};

#endif  // SPACERETARDS_INCLUDE_GUI_PAINTER_PAINTER_H_
