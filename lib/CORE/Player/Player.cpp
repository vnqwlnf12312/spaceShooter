//
// Created by Mac on 02.05.2023.
//

#include "CORE/Player/Player.h"
#include "CORE/Other/future_config.h"
#include "nlohmann/json.hpp"
#include "fstream"

Player::Player() : unlocked_ships(std::vector(global_constants::amount_of_ships, false)) {
  auto json = nlohmann::json::parse(std::ifstream(global_constants::src_dir + "/config.json"));
  balance = json["player"]["balance"];
  for (size_t i = 0; i < json["player"]["unlocked_ships"].size(); ++i) {
    unlocked_ships[i] = json["player"]["unlocked_ships"][i];
  }
}

bool Player::canBuyShip(int ship) {
  return balance >= global_constants::ship_costs[ship];
}

void Player::buyShip(int ship) {
  balance -= global_constants::ship_costs[ship];
  auto json = nlohmann::json::parse(std::ifstream(global_constants::src_dir + "/config.json"));
  json["player"]["unlocked_ships"][ship] = true;
}

int Player::getBalance() {
  return balance;
}

std::vector<bool>& Player::getBoughtShips() {
  return unlocked_ships;
}

void Player::setSelectedShip(ShipType ship) {
  selected_ship = ship;
}

ShipType Player::getSelectedShip() {
  return selected_ship;
}

Player::~Player() {
  auto json = nlohmann::json::parse(std::ifstream(global_constants::src_dir + "/config.json"));
  json["player"]["balance"] = balance;
  json["player"]["unlocked_ships"] = unlocked_ships;
  std::ofstream file(global_constants::src_dir + "/config.json");
  file << json;
}