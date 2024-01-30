//
// Created by Mac on 12.04.2023.
//

#include "GUI/Windows/MainMenu.h"
#include "GUI/Windows/chooseWindow.h"
#include "GUI/Windows/shopWindow.h"
#include "CORE/Other/future_config.h"

int MainMenu::mainPressed() {
  return MainMenuSelected;
}

MainMenu::MainMenu(sf::RenderWindow& main_window, std::shared_ptr<sf::Music> music, const std::shared_ptr<Player>& player) : painter(main_window), music
(music),
player
(player) {
  setting();
}

void MainMenu::setting() {
  unchosen_sprites[0] = Condition{global_constants::SIZE.x / 4, global_constants::SIZE.y / 8, global_constants::SIZE.y / 2, global_constants::SIZE.x / 2};
  chosen_sprites[0] = Condition{global_constants::SIZE.x / 4, global_constants::SIZE.y / 8, global_constants::SIZE.y / 2, global_constants::SIZE.x / 2};

  mainMenu[0] = unchosen_sprites[0];

  unchosen_sprites[1] =
      Condition{global_constants::SIZE.x / 4, global_constants::SIZE.y * 5 / 8, global_constants::SIZE.y / 2, global_constants::SIZE.x / 2, 0};
  chosen_sprites[1] = Condition{global_constants::SIZE.x / 4, global_constants::SIZE.y * 5 / 8, global_constants::SIZE.y / 2, global_constants::SIZE.x / 2, 0};

  mainMenu[1] = unchosen_sprites[1];

  main_menu_sprite = Condition{0, 0, global_constants::SIZE.y, global_constants::SIZE.x};

  MainMenuSelected = -1;
  painter.setMainMenuParameters();

}

void MainMenu::loadMusic() {
  music = std::make_shared<sf::Music>();

  music->openFromFile(global_constants::src_dir + "/Music/menu_music.ogg");

  music->play();
}

MainMenu::~MainMenu() {}

void MainMenu::moveUp() {
  if (MainMenuSelected != -1) {
    mainMenu[MainMenuSelected] = unchosen_sprites[MainMenuSelected];
    int next = (MainMenuSelected + global_constants::menu_size - 1) % global_constants::menu_size;
    mainMenu[next] = chosen_sprites[next];
    MainMenuSelected = next;
  } else {
    MainMenuSelected = 0;
    mainMenu[MainMenuSelected] = chosen_sprites[MainMenuSelected];
  }
  painter.menuButtonChange(MainMenuSelected);
}

void MainMenu::moveDown() {
  if (MainMenuSelected != -1) {
    mainMenu[MainMenuSelected] = unchosen_sprites[MainMenuSelected];
    int next = (MainMenuSelected + 1) % global_constants::menu_size;
    mainMenu[next] = chosen_sprites[next];
    MainMenuSelected = next;
  } else {
    MainMenuSelected = 0;
    mainMenu[MainMenuSelected] = chosen_sprites[MainMenuSelected];
  }
  painter.menuButtonChange(MainMenuSelected);
}

void MainMenu::mouseContains(Point& mouse_pos) {
  if (mainMenu[0].containsPoint(mouse_pos)) {
    MainMenuSelected = 0;
  } else if (mainMenu[1].containsPoint(mouse_pos)) {
    MainMenuSelected = 1;
  }
  painter.menuButtonChange(MainMenuSelected);
}

Window* MainMenu::mousePressed(Point& mouse_pos) {
  if (mainMenu[0].containsPoint(mouse_pos) || mainMenu[1].containsPoint(mouse_pos)) {
    return pickOption();
  }
  return this;
}

Window* MainMenu::pickOption() {
  switch (mainPressed()) {
    case windows::chooseLevel :painter.menuButtonChange(-1);
      return new ChooseWindow(painter.getWindow(), music, player);

    case (windows::shop):painter.menuButtonChange(-1);
      return new ShopWindow(painter.getWindow(), music, player);
  }
  return this;
}

Window* MainMenu::escapePressed() {
  painter.exit();
  return nullptr;
}

void MainMenu::updateWindow() {
  painter.setMainMenuParameters();
  painter.drawBackground(main_menu_sprite);
  painter.drawPlayButton(mainMenu[0]);
  painter.drawShopButton(mainMenu[1]);
  painter.display();
}

