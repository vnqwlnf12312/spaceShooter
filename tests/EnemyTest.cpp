#include "CORE/Bullets/BulletFactory.h"
#include "CORE/Enemies/EnemyFactory.h"
#include <gtest/gtest.h>
#include <memory>
#include <chrono>
#include <thread>




TEST(Enemies, Basic) {
  // пули летят вниз
  auto bul_mov = std::make_shared<Linear>(0, 1);
  auto bul_fac = std::make_shared<BulletFactory>(bul_mov);
  auto enemy_fac = std::make_shared<EnemyFactory>(bul_fac);
  // обычный летит вверх
  auto defaultik = enemy_fac->create(EnemyType::DefaultEnemyType, Point(0, 0), std::make_shared<Linear>(0, -1));
  // неуязвимый летит вниз, стреляет вверх
  auto invincible = enemy_fac->create(EnemyType::InvincibleEnemyType, Point(0, 0), std::make_shared<Linear>(0, 1),
                                      10, std::make_shared<Linear>(0, -1), 20);
  auto hp_in = invincible->getHP();
  auto hp_def = defaultik->getHP();
  invincible->takeDamage(10);
  defaultik->takeDamage(10);
  ASSERT_TRUE(invincible->getHP() == hp_in);
  ASSERT_FALSE(defaultik->getHP() == hp_def);
  ASSERT_TRUE(invincible->getEnemyType() == EnemyType::InvincibleEnemyType);
  ASSERT_TRUE(defaultik->getEnemyType() == EnemyType::DefaultEnemyType);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  ASSERT_TRUE(defaultik->checkShoot());
  auto bul = defaultik->shoot();
  ASSERT_FALSE(defaultik->checkShoot());
  ASSERT_TRUE(bul->getMovement().get() == bul_mov.get());

  ASSERT_TRUE(defaultik->cond.y == invincible->cond.y);
  defaultik->update();
  invincible->update();
  ASSERT_TRUE(defaultik->cond.y < invincible->cond.y);

}

