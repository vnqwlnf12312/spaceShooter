//
// Created by Mac on 14.04.2023.
//

#ifndef PROJECT_INCLUDE_USERTALKER_H_
#define PROJECT_INCLUDE_USERTALKER_H_

#include "string"

#pragma once

class UserMessager {
 public:
  virtual void tellUser(const std::string& message) = 0;
};

class ConsoleMessager : public UserMessager {
 public:
  void tellUser(const std::string& message);
};

#endif  // PROJECT_INCLUDE_USERTALKER_H_
