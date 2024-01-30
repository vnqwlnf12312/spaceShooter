#include "GUI/Painter/PainterLevelWindow.h"
#include "CORE/Other/Condition.h"
#include "CORE/Other/userMessager.h"
#include "CORE/Other/future_config.h"

PainterLevelWindow::PainterLevelWindow(sf::RenderWindow& main_window, int choLevel) : Painter(main_window), choosed_level(choLevel) {}

PainterLevelWindow::~PainterLevelWindow() {}

void PainterLevelWindow::setLevelWindowParameters() {

  if (levelWindowLoaded) {
    return;
  }
  ConsoleMessager messager;

  std::map<BulletType, std::string> BulletPaths = {
    std::make_pair(SimpleBullet, global_constants::src_dir + "/assets/SimpleBullet.png"),
    std::make_pair(TriangleBullet, global_constants::src_dir + "/assets/TriangleBullet.png"),
    std::make_pair(BigCircleBullet, global_constants::src_dir + "/assets/BigCircleBullet.png"),
    std::make_pair(PercentDamageBullet, global_constants::src_dir + "/assets/PercentDamageBullet.png"),
  };
  std::map<EnemyType, std::string> EnemyPaths = {
    std::make_pair(DefaultEnemyType, global_constants::src_dir + "/assets/BasicDaun.png"),
    std::make_pair(ToughEnemyType, global_constants::src_dir + "/assets/ToughDaun.png"),
    //std::make_pair(InvincibleEnemyType, global_constants::src_dir + "/assets/Hitler.png"),
    //std::make_pair(BossType, global_constants::src_dir + "/assets/BIGMADGITLER.png"),
  };
  std::map<int, std::string> BackgroundPaths = {
    std::make_pair(0, global_constants::src_dir + "/assets/firstLevelBackground.png"),
    std::make_pair(1, global_constants::src_dir + "/assets/secondLevelBackground.png")
  };
  std::map<ShipType, std::string> ShipPaths = {
    std::make_pair(BasicShip, global_constants::src_dir + "/assets/defaultShip.png"),
    std::make_pair(TripleShotShip, global_constants::src_dir + "/assets/ship1.png")
  };

  for (auto type : BulletPrototype::BulletTypeIter) {
    BulletSprites[type] = sf::Sprite();
    BulletTextures[type] = sf::Texture();
    if (!BulletTextures[type].loadFromFile(BulletPaths[type])) {
      messager.tellUser("can't load " + BulletPaths[type]);
    }
    BulletSprites[type].setTexture(BulletTextures[type]);
  }

  for (auto type : EnemyPrototype::EnemyTypeIter) {
    EnemySprites[type] = sf::Sprite();
    EnemyTextures[type] = sf::Texture();
    if (!EnemyTextures[type].loadFromFile(EnemyPaths[type])) {
      messager.tellUser("can't load " + EnemyPaths[type]);
    }
    EnemySprites[type].setTexture(EnemyTextures[type]);
  }

  for (auto type : ShipPrototype::ShipTypeIter) {
    ShipSprites[type] = sf::Sprite();
    ShipTextures[type] = sf::Texture();
    if (!ShipTextures[type].loadFromFile(ShipPaths[type])) {
      messager.tellUser("can't load " + ShipPaths[type]);
    }
    ShipSprites[type].setTexture(ShipTextures[type]);
  }

  for (int i = 0; i < level_count; ++i) {
    LevelBackgroundTextures[i] = sf::Texture();
    LevelBackgroundSprites[i] = sf::Sprite();
    if (!LevelBackgroundTextures[i].loadFromFile(BackgroundPaths[i])) {
      messager.tellUser("can't load" + BackgroundPaths[i]);
    };
    LevelBackgroundSprites[i].setTexture(LevelBackgroundTextures[i]);
    LevelBackgroundSprites[i].scale(global_constants::SIZE.x / LevelBackgroundSprites[i].getGlobalBounds().width,
                                    global_constants::SIZE.y / LevelBackgroundSprites[i].getGlobalBounds().height);
  }
  levelWindowLoaded = true;
}

void PainterLevelWindow::changeLevel(int new_level) {
  choosed_level = new_level;
}

void PainterLevelWindow::drawBackground() {
  main_window.draw(LevelBackgroundSprites[choosed_level]);
}

void PainterLevelWindow::drawPlayer(std::unique_ptr<ShipPrototype>& player) {
  sf::Sprite cur = ShipSprites[player->getShipType()];
  Condition cond = player->cond;
  cur.setScale(cond.width / cur.getGlobalBounds().width, 
               cond.height / cur.getGlobalBounds().height);
  cur.setPosition(cond.x, cond.y);
  cur.setRotation(cond.rotation);
  main_window.draw(cur);
}

void PainterLevelWindow::drawEnemy(std::unique_ptr<EnemyPrototype>& enemy) {
  fixSprite(EnemySprites[enemy->getEnemyType()], enemy->cond);
  main_window.draw(EnemySprites[enemy->getEnemyType()]);
}

void PainterLevelWindow::drawBullet(std::unique_ptr<BulletPrototype>& bullet) {
  sf::Sprite cur = BulletSprites[bullet->getBulletType()];
  cur.setOrigin(sf::Vector2f(cur.getTexture()->getSize().x * 0.5, cur.getTexture()->getSize().y * 0.5));
  fixSprite(cur, bullet->cond);
  main_window.draw(cur);
}

void PainterLevelWindow::drawLevel(std::unique_ptr<ShipPrototype>& player, std::vector<std::unique_ptr<EnemyPrototype>>& enemies,
                        std::vector<std::unique_ptr<BulletPrototype>>& enemy_bullets,
                        std::vector<std::unique_ptr<BulletPrototype>>& hero_bullets) {
  drawBackground();
  drawPlayer(player);
  for (auto& iter: enemies) {
    drawEnemy(iter);
  }
  for (auto& iter: enemy_bullets) {
    drawBullet(iter);
  }
  for (auto& iter: hero_bullets) {
    drawBullet(iter);
  }
  main_window.display();
}
