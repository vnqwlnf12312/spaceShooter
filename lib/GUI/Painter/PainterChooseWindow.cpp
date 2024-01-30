#include "GUI/Painter/PainterChooseWindow.h"
#include "CORE/Other/Condition.h"
#include "CORE/Other/userMessager.h"
#include "CORE/Other/future_config.h"

PainterChooseWindow::PainterChooseWindow(sf::RenderWindow& main_window) : Painter(main_window) {}

void PainterChooseWindow::setChooseWindowParameters() {
  if (chooseWindowLoaded) {
    return;
  }
  ConsoleMessager messager;
  if (!chooseWindowBackgroundTexture.loadFromFile(
      global_constants::src_dir + "/assets/chooseLevel.png")) {
    messager.tellUser("can't load chooseLever.png");
  }
  chooseWindowBackgroundSprite.setTexture(chooseWindowBackgroundTexture);

  if (!chooseWindowChosenLevelTexture[0].loadFromFile(
      global_constants::src_dir + "/assets/first.png")) {
    messager.tellUser("can't load first.png");
  }
  chooseWindowLevelSprite[0].setTexture(chooseWindowChosenLevelTexture[0]);

  if (!chooseWindowChosenLevelTexture[1].loadFromFile(
      global_constants::src_dir + "/assets/second.png")) {
    messager.tellUser("can't load second.png");
  }
  chooseWindowLevelSprite[1].setTexture(chooseWindowChosenLevelTexture[1]);

  if (!switchLevelLeftTexture.loadFromFile(global_constants::src_dir + "/assets/switchButtonLeft.png")) {
    messager.tellUser("can't load switchButtonLeft.png");
  }
  switchLevelLeftSprite.setTexture(switchLevelLeftTexture);

  if (!switchLevelRightTexture.loadFromFile(global_constants::src_dir + "/assets/switchButtonRight.png")) {
    messager.tellUser("can't load switchButtonRight.png");
  }
  switchLevelRightSprite.setTexture(switchLevelRightTexture);

  chooseWindowLoaded = true;
}

void PainterChooseWindow::drawBackground(const Condition& cond) {
  fixSprite(chooseWindowBackgroundSprite, cond);
  main_window.draw(chooseWindowBackgroundSprite);
}

void PainterChooseWindow::drawLevelButton(const Condition& cond) {
  fixSprite(chooseWindowLevelSprite[cur_level], cond);
  main_window.draw(chooseWindowLevelSprite[cur_level]);
}

void PainterChooseWindow::drawSwitchLeftButton(const Condition& cond) {
  fixSprite(switchLevelLeftSprite, cond);
  main_window.draw(switchLevelLeftSprite);
}

void PainterChooseWindow::drawSwitchRightButton(const Condition& cond) {
  fixSprite(switchLevelRightSprite, cond);
  main_window.draw(switchLevelRightSprite);
}

void PainterChooseWindow::chooseButtonChange(int choosedButton) {
  cur_level = choosedButton;
}

PainterChooseWindow::~PainterChooseWindow() {}
