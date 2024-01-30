//
// Created by Mac on 19.03.2023.
//

#ifndef PROJECT_HEADERS_FUTURE_CONFIG_H_
#define PROJECT_HEADERS_FUTURE_CONFIG_H_

#include <SFML/Graphics.hpp>

#include "CORE/Other/Condition.h"

#pragma once

namespace global_constants {
const Point SIZE = {960, 720};
const std::string src_dir = SRC_DIR;
const int amount_of_levels = 2;
const int amount_of_ships = 2;
const int menu_size = 2;
const int fps = 60;
const sf::Time mouse_click_delay = sf::milliseconds(300);
const std::vector<int> ship_costs = {100, 1000};
const std::string first_ship_desc = "Obichnii korabl, strelayet s kaifom";
const std::string second_ship_desc =
    "Krutoy korabl, strelayet srazu tremya pulyami!!";
}  // namespace global_constants

#endif  // PROJECT_HEADERS_FUTURE_CONFIG_H_
