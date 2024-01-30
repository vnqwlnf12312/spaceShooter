//
// Created by Mac on 12.04.2023.
//

#include "GUI/Windows/chooseWindow.h"
#include "GUI/Windows/MainMenu.h"
#include "CORE/Other/future_config.h"

int ChooseWindow::levelPressed() {
  return level_selected;
}

ChooseWindow::ChooseWindow(sf::RenderWindow& main_window, std::shared_ptr<sf::Music> music, const std::shared_ptr<Player>& player):level_selected(0), painter
(main_window), player(player),
music(music)  {
  setting();
}

void ChooseWindow::setting() {
  float x = global_constants::SIZE.x, y = global_constants::SIZE.y;

  choose_level_sprite = Condition{0, 0, y, x, 0};
  levels_sprites[0] = Condition{x / 4, y / 2, y / 4, x / 4, 0};
  levels_sprites[1] = Condition{x / 4, y / 2, y / 4, x / 4, 0};

  switch_left_sprite = Condition{x / 8, y * 3 / 4, y / 8, x / 8, 0};
  switch_right_sprite = Condition{x * 6 / 8, y * 3 / 4, y / 8, x / 8, 0};
  painter.setChooseWindowParameters();
}


void ChooseWindow::moveLeft() {
  level_selected = (global_constants::amount_of_levels + level_selected - 1) % global_constants::amount_of_levels;
  painter.chooseButtonChange(level_selected);
}

void ChooseWindow::moveRight() {
  level_selected = (global_constants::amount_of_levels + level_selected + 1) % global_constants::amount_of_levels;
  painter.chooseButtonChange(level_selected);
}

Window* ChooseWindow::mousePressed(Point& mouse_pos) {
  if (switch_left_sprite.containsPoint(mouse_pos)) {
    moveLeft();
  } else if (switch_right_sprite.containsPoint(mouse_pos)) {
    moveRight();
  }
  if (levels_sprites[0].containsPoint(mouse_pos)) {
    return pickOption();
  }
  return this;
}

Window* ChooseWindow::pickOption() {
  music->stop();
  LevelWindow* to_return;
  switch (level_selected) {
    case 0:
      to_return = new LevelWindow(painter.getWindow(), player, level_selected);
      to_return->startLevel();
      break;
    case 1:
      to_return = new LevelWindow(painter.getWindow(), player, level_selected);
      to_return->startLevel();
      break;
  }
  return to_return;
}

void ChooseWindow::updateWindow() {
  painter.setChooseWindowParameters();
  painter.drawBackground(choose_level_sprite);
  painter.drawLevelButton(levels_sprites[level_selected]);
  painter.drawSwitchLeftButton(switch_left_sprite);
  painter.drawSwitchRightButton(switch_right_sprite);
  painter.display();
}

Window* ChooseWindow::escapePressed() {
  return new MainMenu(painter.getWindow(), music, player);
}

void ChooseWindow::loadMusic() {
  music = std::make_shared<sf::Music>();

  music->openFromFile(global_constants::src_dir + "/Music/menu_music.ogg");

  music->play();
}
