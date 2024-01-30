//
// Created by Mac on 15.04.2023.
//

#ifndef PROJECT_INCLUDE_CONTROLLER_H_
#define PROJECT_INCLUDE_CONTROLLER_H_

#include <SFML/Graphics.hpp>

#include "GUI/Painter/PainterMainMenu.h"
#include "GUI/Windows/window.h"

#pragma once

class Controller {
 public:
  Controller(sf::RenderWindow& main_window);
  void startMenu();
  void update();
  void keyReleased(sf::Event& event);
  void keyPressed(sf::Event& event);
  void mouseContains();
  void mousePressed();

 private:
  sf::RenderWindow& main_window;
  std::unique_ptr<Window> cur_window;
  sf::Clock clock;
};

#endif  // PROJECT_INCLUDE_CONTROLLER_H_
