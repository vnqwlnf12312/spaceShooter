//
// Created by Mac on 15.04.2023.
//

#include "GUI/Windows/window.h"

Window* Window::pickOption() {
  return this;
}

void Window::moveRight() {}

void Window::moveLeft() {}

void Window::moveDown() {}

void Window::moveUp() {}

void Window::leftPressed() {}

void Window::rightPressed() {}

void Window::downPressed() {}

void Window::upPressed() {}

void Window::wPressed() {}

void Window::aPressed() {}

void Window::sPressed() {}

void Window::dPressed() {}

void Window::mouseContains(Point& mouse_pos) {}

Window* Window::mousePressed(Point& mouse_pos) {
  return this;
}

void Window::updateWindow() {}

void Window::loadMusic() {}

Window* Window::escapePressed() {
  return this;
}
