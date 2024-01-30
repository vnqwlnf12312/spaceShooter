#include <SFML/Graphics.hpp>
#include <iostream>

#include "CORE/Other/future_config.h"
#include "GUI/Controller/controller.h"

int main() {
  sf::RenderWindow main_window(
      sf::VideoMode(global_constants::SIZE.x, global_constants::SIZE.y),
      "SpaceRetards", sf::Style::Default);
  Controller controller(main_window);
  controller.startMenu();
  return 0;
}

// stringstream