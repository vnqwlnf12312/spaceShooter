//
// Created by Mac on 15.04.2023.
//

#include "GUI/Controller/controller.h"
#include "GUI/Windows/MainMenu.h"
#include "CORE/Other/future_config.h"

Controller::Controller(sf::RenderWindow& main_window) : main_window(main_window) {
  clock.restart();
}

void Controller::startMenu() {
  cur_window = std::make_unique<MainMenu>(main_window, nullptr);
  main_window.setFramerateLimit(global_constants::fps);
  cur_window->loadMusic();
  while (main_window.isOpen()) {
    update();
  }
}

void Controller::update() {
  mouseContains();
  sf::Event event;
  while (main_window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed :
        main_window.close();
        break;
      case sf::Event::MouseButtonReleased :
        mousePressed();
        break;
    }
    if (event.type == sf::Event::KeyReleased) {
      keyReleased(event);
    }
    if (event.type == sf::Event::KeyPressed) {
      keyPressed(event);
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    cur_window->wPressed();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    cur_window->aPressed();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    cur_window->sPressed();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    cur_window->dPressed();
  }
  if (cur_window == nullptr) {
    return;
  }
  cur_window->updateWindow();
}

void Controller::keyPressed(sf::Event& event) {
  if (event.key.code == sf::Keyboard::Up) {
    cur_window->upPressed();
  }
  if (event.key.code == sf::Keyboard::Down) {
    cur_window->downPressed();
  }
  if (event.key.code == sf::Keyboard::Left) {
    cur_window->leftPressed();
  }
  if (event.key.code == sf::Keyboard::Right) {
    cur_window->rightPressed();
  }
  if (event.key.code == sf::Keyboard::Escape) {
    //cur_window = cur_window->escapePressed();
  }
  if (event.key.code == sf::Keyboard::Enter) {
    //cur_window = cur_window->pickOption();
  }
}

void Controller::keyReleased(sf::Event& event) {
  if (event.key.code == sf::Keyboard::Up) {
    cur_window->moveUp();
  }
  if (event.key.code == sf::Keyboard::Down) {
    cur_window->moveDown();
  }
  if (event.key.code == sf::Keyboard::Left) {
    cur_window->moveLeft();
  }
  if (event.key.code == sf::Keyboard::Right) {
    cur_window->moveRight();
  }
  if (event.key.code == sf::Keyboard::Escape) {
    Window* new_window = cur_window->escapePressed();
    if (!(new_window == cur_window.get())) {
      cur_window.reset(new_window);
    }
  }
  if (event.key.code == sf::Keyboard::Enter) {
    Window* new_window = cur_window->pickOption();
    if (!(new_window == cur_window.get())) {
      cur_window.reset(new_window);
    }
  }
}

void Controller::mouseContains() {
  sf::Vector2i mouse_position = sf::Mouse::getPosition(main_window);
  Point mouse_pos = {static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y)};
  cur_window->mouseContains(mouse_pos);
}

void Controller::mousePressed() {
  sf::Vector2i mouse_position = sf::Mouse::getPosition(main_window);
  Point mouse_pos = {static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y)};
  Window* new_window = cur_window->mousePressed(mouse_pos);
  if (!(new_window == cur_window.get())) {
    cur_window.reset(new_window);
  }
}
