#include "GUI/Painter/PainterShopWindow.h"
#include "CORE/Other/Condition.h"
#include "CORE/Other/userMessager.h"
#include "CORE/Other/future_config.h"
#include "CORE/Player/Player.h"


PainterShopWindow::PainterShopWindow(sf::RenderWindow& main_window) : Painter(main_window) {}

void PainterShopWindow::setShopWindowParameters() {
  if (shopWindowLoaded) {
    return;
  }
  ConsoleMessager messager;
  if (!shopWindowBackgroundTexture.loadFromFile(global_constants::src_dir + "/assets/shop.png")) {
    messager.tellUser("can't load shop.png");
  }
  shopWindowBackgroundSprite.setTexture(shopWindowBackgroundTexture);

  if (!shopWindowShipTexture[0].loadFromFile(global_constants::src_dir + "/assets/defaultShip.png")) {
    messager.tellUser("can't load defaultShip.png");
  }
  shopWindowShipSprite[0].setTexture(shopWindowShipTexture[0]);

  if (!shopWindowShipTexture[1].loadFromFile(
      global_constants::src_dir + "/assets/ship1.png")) {
    messager.tellUser("can't load ship1.png");
  }
  shopWindowShipSprite[1].setTexture(shopWindowShipTexture[1]);

  if (!switchShipLeftTexture.loadFromFile(global_constants::src_dir + "/assets/switchButtonLeft.png")) {
    messager.tellUser("can't load switchButtonLeft.png");
  }
  switchShipLeftSprite.setTexture(switchShipLeftTexture);

  if (!switchShipRightTexture.loadFromFile(global_constants::src_dir + "/assets/switchButtonRight.png")) {
    messager.tellUser("can't load switchButtonRight.png");
  }
  switchShipRightSprite.setTexture(switchShipRightTexture);

  if (!balanceTextTexture.loadFromFile(global_constants::src_dir + "/assets/balance.png")) {
    messager.tellUser("can't load balance.png");
  }

  balanceTextSprite.setTexture(balanceTextTexture);

  if (!buyTexture.loadFromFile(global_constants::src_dir + "/assets/buy.png")) {
    messager.tellUser("can't load buy.png");
  }

  buySprite.setTexture(buyTexture);

  if (!boughtTexture.loadFromFile(global_constants::src_dir + "/assets/bought.png")) {
    messager.tellUser("can't load bought.png");
  }

  boughtSprite.setTexture(boughtTexture);

  if (!selectTexture.loadFromFile(global_constants::src_dir + "/assets/select.png")) {
    messager.tellUser("can't load select.png");
  }

  selectSprite.setTexture(selectTexture);

  font.loadFromFile(global_constants::src_dir + "/FrozencaScriptTypeface.ttf");


  balance.setFont(font);
  balance.setFillColor(sf::Color::Black);
  price.setFont(font);
  price.setFillColor(sf::Color::Black);

  descriptions.resize(2);

  descriptions[0].setString(global_constants::first_ship_desc);
  descriptions[0].setFont(font);
  descriptions[0].setFillColor(sf::Color::Black);

  descriptions[1].setString(global_constants::second_ship_desc);
  descriptions[1].setFont(font);
  descriptions[1].setFillColor(sf::Color::Black);

  shopWindowLoaded = true;
}

void PainterShopWindow::drawBackground(const Condition& cond) {
  fixSprite(shopWindowBackgroundSprite, cond);
  main_window.draw(shopWindowBackgroundSprite);
}

void PainterShopWindow::drawShip(const Condition& cond) {
  fixSprite(shopWindowShipSprite[choosed_ship], cond);
  main_window.draw(shopWindowShipSprite[choosed_ship]);
}

void PainterShopWindow::drawSwitchLeftButton(const Condition& cond) {
  fixSprite(switchShipLeftSprite, cond);
  main_window.draw(switchShipLeftSprite);
}

void PainterShopWindow::drawSwitchRightButton(const Condition& cond) {
  fixSprite(switchShipRightSprite, cond);
  main_window.draw(switchShipRightSprite);
}

void PainterShopWindow::drawBalanceText(const Condition& cond) {
  fixSprite(balanceTextSprite, cond);
  main_window.draw(balanceTextSprite);
}

void PainterShopWindow::drawBalance(const Condition& cond) {
  fixText(balance, cond);
  main_window.draw(balance);
}

void PainterShopWindow::drawBuyText(const Condition& cond, std::shared_ptr<Player>& player) {
  if (player->getBoughtShips()[choosed_ship]) {
    if (player->getSelectedShip() == choosed_ship) {
      fixSprite(boughtSprite, cond);
      main_window.draw(boughtSprite);
      return;
    }
    fixSprite(selectSprite, cond);
    main_window.draw(selectSprite);
    return;
  }
  fixSprite(buySprite, cond);
  main_window.draw(buySprite);
}

void PainterShopWindow::drawPrice(const Condition& cond) {
  fixText(price, cond);
  main_window.draw(price);
}

void PainterShopWindow::drawDescription(const Condition& cond) {
  fixText(descriptions[choosed_ship], cond);
  main_window.draw(descriptions[choosed_ship]);
}

void PainterShopWindow::shopButtonChange(int choosedButton) {
  choosed_ship = choosedButton;
  setPrice(global_constants::ship_costs[choosed_ship]);
}

void PainterShopWindow::setBalance(int new_balance) {
  balance.setString(std::to_string(new_balance));
}

void PainterShopWindow::setPrice(int new_price) {
  price.setString(std::to_string(new_price));
}

PainterShopWindow::~PainterShopWindow() {}