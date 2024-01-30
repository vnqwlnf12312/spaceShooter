//
// Created by Mac on 14.04.2023.
//

#include "CORE/Other/userMessager.h"
#include "iostream"

void ConsoleMessager::tellUser(const std::string& message) {
  std::cout << message << std::endl;
}