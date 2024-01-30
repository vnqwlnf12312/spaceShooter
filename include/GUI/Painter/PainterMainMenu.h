#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "CORE/Other/future_config.h"
#include "GUI/Painter/Painter.h"

#pragma once

class PainterMainMenu : public Painter {
 public:
  PainterMainMenu(sf::RenderWindow& mainWindow);

  void setMainMenuParameters();
  void menuButtonChange(int choosedButton);
  void drawBackground(const Condition& cond);
  void drawPlayButton(const Condition& cond);
  void drawShopButton(const Condition& cond);

  ~PainterMainMenu();

 private:
  bool mainMenuLoaded = false;
  sf::Texture mainMenuUnchosenButtonTexture[global_constants::menu_size];
  sf::Texture mainMenuChosenButtonTexture[global_constants::menu_size];
  sf::Sprite mainMenuButtonSprite[global_constants::menu_size];
  sf::Texture mainMenuBackgroundTexture;
  sf::Sprite mainMenuBackgroundSprite;
};
