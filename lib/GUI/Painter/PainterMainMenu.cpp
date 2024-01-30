#include "GUI/Painter/PainterMainMenu.h"
#include "CORE/Other/Condition.h"
#include "CORE/Other/userMessager.h"
#include "CORE/Other/future_config.h"

PainterMainMenu::PainterMainMenu(sf::RenderWindow& main_window) : Painter(main_window) {}

void PainterMainMenu::setMainMenuParameters() {
  if (mainMenuLoaded) {
    return;
  }
  ConsoleMessager messager;
  if (!mainMenuBackgroundTexture.loadFromFile(global_constants::src_dir + "/assets/mainMenu.png")) {
    messager.tellUser("can't loat mainMenu.png");
  }
  mainMenuBackgroundSprite.setTexture(mainMenuBackgroundTexture);

  if (!mainMenuUnchosenButtonTexture[0].loadFromFile(
      global_constants::src_dir + "/assets/chooseLevelUnchosen.png")) {
    messager.tellUser("cant load chooseLevelUnchosen.png");
  }

  if (!mainMenuChosenButtonTexture[0].loadFromFile(
      global_constants::src_dir + "/assets/chooseLevelChosen.png")) {
    messager.tellUser("cant't load chooseLeverChosen.png");
  }
  mainMenuButtonSprite[0].setTexture(mainMenuUnchosenButtonTexture[0]);

  if (!mainMenuUnchosenButtonTexture[1].loadFromFile(
      global_constants::src_dir + "/assets/shopButtonUnchosen.png")) {
    messager.tellUser("can't load shotButtonUnchosen.png");
  }
  if (!mainMenuChosenButtonTexture[1].loadFromFile(
      global_constants::src_dir + "/assets/shopButtonChosen.png")) {
    messager.tellUser("can't load shopButtonChosen.png");
  }
  mainMenuButtonSprite[1].setTexture(mainMenuUnchosenButtonTexture[1]);
  mainMenuLoaded = true;
}

PainterMainMenu::~PainterMainMenu() {}

void PainterMainMenu::drawBackground(const Condition& cond) {
  fixSprite(mainMenuBackgroundSprite, cond);
  main_window.draw(mainMenuBackgroundSprite);
}

void PainterMainMenu::drawPlayButton(const Condition& cond) {
  fixSprite(mainMenuButtonSprite[0], cond);
  main_window.draw(mainMenuButtonSprite[0]);
}

void PainterMainMenu::drawShopButton(const Condition& cond) {
  fixSprite(mainMenuButtonSprite[1], cond);
  main_window.draw(mainMenuButtonSprite[1]);
}

void PainterMainMenu::menuButtonChange(int choosedButton) {
  for (int i = 0; i < global_constants::menu_size; ++i) {
    mainMenuButtonSprite[i].setTexture(mainMenuUnchosenButtonTexture[i]);
  }
  if (choosedButton == -1) {
    return;
  }
  mainMenuButtonSprite[choosedButton].setTexture(mainMenuChosenButtonTexture[choosedButton]);
}

