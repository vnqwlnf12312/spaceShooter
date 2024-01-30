//
// Created by Mac on 12.04.2023.
//

#include "GUI/Windows/shopWindow.h"
#include "GUI/Windows/MainMenu.h"
#include "CORE/Other/future_config.h"
#include "CORE/Player/Player.h"

int ShopWindow::shipPressed() {
  return cur_ship;
}

ShopWindow::~ShopWindow() {}

ShopWindow::ShopWindow(sf::RenderWindow& main_window, std::shared_ptr<sf::Music> music, const std::shared_ptr<Player>& player) : cur_ship
(ShipType::BasicShip), painter(main_window), music(music), player(player) {
  setting();
}

void ShopWindow::setting() {
  shop_sprite = Condition{0, 0, global_constants::SIZE.y, global_constants::SIZE.x, 0};

  ship = Condition{global_constants::SIZE.x / 2, global_constants::SIZE.y / 4, global_constants::SIZE.y / 8, global_constants::SIZE.x / 4};
  switch_ship_left = Condition{global_constants::SIZE.x / 8, global_constants::SIZE.y * 3 / 4, global_constants::SIZE.y / 8, global_constants::SIZE.x / 8};
  switch_ship_right = Condition{global_constants::SIZE.x * 6 / 8, global_constants::SIZE.y * 3 / 4, global_constants::SIZE.y / 8, global_constants::SIZE.x / 8};

  balance_text = Condition{global_constants::SIZE.x / 8, global_constants::SIZE.y / 16, global_constants::SIZE.y / 4, global_constants::SIZE.x / 4};
  balance = Condition(global_constants::SIZE.x / 8, global_constants::SIZE.y * 5 / 16, global_constants::SIZE.y / 4 , global_constants::SIZE.x / 4);
  buy = Condition{global_constants::SIZE.x / 2, global_constants::SIZE.y * 3 / 8, global_constants::SIZE.y / 8, global_constants::SIZE.x / 8};
  price = Condition{global_constants::SIZE.x / 2, global_constants::SIZE.y / 2, global_constants::SIZE.y / 4, global_constants::SIZE.x / 8};

  painter.setBalance(player->getBalance());
  painter.setPrice(global_constants::ship_costs[cur_ship]);

  description = Condition{global_constants::SIZE.x / 4, global_constants::SIZE.y * 3 / 4, global_constants::SIZE.y / 6, global_constants::SIZE.x / 2};
}

void ShopWindow::moveLeft() {
  cur_ship = static_cast<ShipType>((global_constants::amount_of_ships + static_cast<int>(cur_ship) - 1) % global_constants::amount_of_ships);
  painter.shopButtonChange(cur_ship);
}

void ShopWindow::moveRight() {
  cur_ship = static_cast<ShipType>((global_constants::amount_of_ships + static_cast<int>(cur_ship) + 1) % global_constants::amount_of_ships);
  painter.shopButtonChange(cur_ship);
}

Window* ShopWindow::mousePressed(Point& mouse_pos) {
  if (switch_ship_left.containsPoint(mouse_pos)) {
    moveLeft();
  } else if (switch_ship_right.containsPoint(mouse_pos)) {
    moveRight();
  } else if (buy.containsPoint(mouse_pos)) {
    pickOption();
  }
  return this;
}

Window* ShopWindow::pickOption() {
  if (player->canBuyShip(cur_ship) && !player->getBoughtShips()[cur_ship]) {
    player->buyShip(cur_ship);
    painter.setBalance(player->getBalance());
    player->getBoughtShips()[cur_ship] = true;
  }
  player->setSelectedShip(cur_ship);
  return this;
}

void ShopWindow::updateWindow() {
  painter.setShopWindowParameters();
  painter.drawBackground(shop_sprite);
  painter.drawShip(ship);
  painter.drawSwitchLeftButton(switch_ship_left);
  painter.drawSwitchRightButton(switch_ship_right);
  painter.drawBalanceText(balance_text);
  painter.drawBalance(balance);
  painter.drawBuyText(buy, player);
  painter.drawPrice(price);
  painter.drawDescription(description);
  painter.display();
}

Window* ShopWindow::escapePressed() {
  return new MainMenu(painter.getWindow(), music, player);
}
