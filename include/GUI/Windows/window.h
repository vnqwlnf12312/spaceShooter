//
// Created by Mac on 15.04.2023.
//

#ifndef PROJECT_INCLUDE_WINDOW_H_
#define PROJECT_INCLUDE_WINDOW_H_

#include "CORE/Other/Condition.h"
#include "memory"

#pragma once

class Window {
 public:
  virtual void moveUp();
  virtual void moveDown();
  virtual void moveLeft();
  virtual void moveRight();
  virtual void upPressed();
  virtual void downPressed();
  virtual void leftPressed();
  virtual void rightPressed();
  virtual void wPressed();
  virtual void aPressed();
  virtual void sPressed();
  virtual void dPressed();
  virtual Window* escapePressed();
  virtual void mouseContains(Point& mouse_pos);
  virtual Window* mousePressed(Point& mouse_pos);
  virtual Window* pickOption();
  virtual void updateWindow();
  virtual void loadMusic();
  virtual ~Window() = default;
};

#endif  // PROJECT_INCLUDE_WINDOW_H_
