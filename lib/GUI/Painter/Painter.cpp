#include "GUI/Painter/Painter.h"
#include "CORE/Other/Condition.h"
#include "CORE/Other/userMessager.h"
#include "CORE/Other/future_config.h"

Painter::Painter(sf::RenderWindow& main_window) : main_window(main_window) {
}

sf::RenderWindow& Painter::getWindow() {
  return main_window;
}

void Painter::exit() {
  main_window.close();
}

void Painter::fixSprite(sf::Sprite& sprite, const Condition& cond) {
  sprite.setPosition(cond.x, cond.y);
  sprite.scale(cond.width / sprite.getGlobalBounds().width,
               cond.height / sprite.getGlobalBounds().height);
  sprite.setRotation(cond.rotation);
}

void Painter::fixText(sf::Text& text, const Condition& cond) {
  text.setPosition(cond.x, cond.y);
  text.scale(cond.width / text.getGlobalBounds().width,
                  cond.height / text.getGlobalBounds().height);
  text.setRotation(cond.rotation);
}

void Painter::display() {
  main_window.display();
}