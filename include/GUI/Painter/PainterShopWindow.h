#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

#include "CORE/Other/future_config.h"
#include "CORE/Player/Player.h"
#include "GUI/Painter/Painter.h"

#pragma once

class PainterShopWindow : public Painter {
 public:
  PainterShopWindow(sf::RenderWindow& mainWindow);

  void setShopWindowParameters();
  void drawBackground(const Condition& cond);
  void drawShip(const Condition& cond);
  void drawSwitchLeftButton(const Condition& cond);
  void drawSwitchRightButton(const Condition& cond);
  void drawBalanceText(const Condition& cond);
  void drawBalance(const Condition& cond);
  void drawBuyText(const Condition& cond, std::shared_ptr<Player>& player);
  void drawDescription(const Condition& cond);
  void drawPrice(const Condition& cond);

  void setBalance(int new_balance);
  void setPrice(int new_price);

  void shopButtonChange(int choosedButton);

  ~PainterShopWindow();

 private:
  bool shopWindowLoaded = false;

  sf::Texture shopWindowShipTexture[global_constants::amount_of_ships];
  sf::Sprite shopWindowShipSprite[global_constants::amount_of_ships];
  sf::Texture shopWindowBackgroundTexture;
  sf::Sprite shopWindowBackgroundSprite;
  sf::Texture switchShipLeftTexture;
  sf::Sprite switchShipLeftSprite;
  sf::Texture switchShipRightTexture;
  sf::Sprite switchShipRightSprite;
  sf::Texture balanceTextTexture;
  sf::Sprite balanceTextSprite;
  sf::Text balance;
  sf::Texture buyTexture;
  sf::Sprite buySprite;
  sf::Texture boughtTexture;
  sf::Sprite boughtSprite;
  sf::Texture selectTexture;
  sf::Sprite selectSprite;
  sf::Text price;
  std::vector<sf::Text> descriptions;
  sf::Font font;
  int choosed_ship = 0;
};
