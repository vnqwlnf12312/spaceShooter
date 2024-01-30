//
// Created by Mac on 02.05.2023.
//

#ifndef SPACERETARDS_LIB_CORE_PLAYER_PLAYER_H_
#define SPACERETARDS_LIB_CORE_PLAYER_PLAYER_H_

#include "CORE/Hero/Hero.h"
#include "vector"

#pragma once

class Player {
 public:
  Player();
  bool canBuyShip(int ship);
  void buyShip(int ship);
  void setSelectedShip(ShipType ship);
  ShipType getSelectedShip();
  int getBalance();
  std::vector<bool>& getBoughtShips();
  ~Player();

 private:
  int balance;
  std::vector<bool> unlocked_ships;
  ShipType selected_ship = ShipType::BasicShip;
};

#endif  // SPACERETARDS_LIB_CORE_PLAYER_PLAYER_H_
