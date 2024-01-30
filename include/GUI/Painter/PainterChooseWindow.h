#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "CORE/Other/future_config.h"
#include "GUI/Painter/Painter.h"

#pragma once

class PainterChooseWindow : public Painter {
 public:
  PainterChooseWindow(sf::RenderWindow& mainWindow);

  void setChooseWindowParameters();
  void drawBackground(const Condition& cond);
  void drawLevelButton(const Condition& cond);
  void drawSwitchLeftButton(const Condition& cond);
  void drawSwitchRightButton(const Condition& cond);
  void chooseButtonChange(int choosedButton);

  ~PainterChooseWindow();

 private:
  bool chooseWindowLoaded = false;

  sf::Texture
      chooseWindowChosenLevelTexture[global_constants::amount_of_levels];
  sf::Sprite chooseWindowLevelSprite[global_constants::amount_of_levels];
  sf::Texture chooseWindowBackgroundTexture;
  sf::Sprite chooseWindowBackgroundSprite;
  sf::Texture switchLevelLeftTexture;
  sf::Sprite switchLevelLeftSprite;
  sf::Texture switchLevelRightTexture;
  sf::Sprite switchLevelRightSprite;

  int cur_level = 0;
};
