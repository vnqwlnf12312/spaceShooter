#include "CORE/Bullets/BulletFactory.h"
#include "CORE/Enemies/EnemyFactory.h"
#include <gtest/gtest.h>
#include <memory>


TEST(Bullets, Basic) {
  float hp = 100.f;
  float speed = 100.f;
  // пули летят вверх
  auto bul_fac = std::make_shared<BulletFactory>(std::make_shared<Linear>(0, -1));
  auto simple = bul_fac->create(BulletType::SimpleBullet, Point(0, 0));
  auto circle = bul_fac->create(BulletType::BigCircleBullet, Point(0, 0), std::make_shared<Linear>(1, 1));
  auto triangle = bul_fac->create(BulletType::TriangleBullet, Point(0, 0), speed);
  auto percent = bul_fac->create(BulletType::PercentDamageBullet, Point(0, 0), std::make_shared<Linear>(1, 1), speed);
  ASSERT_TRUE(simple->CalculateDamage(hp) == 5);
  ASSERT_TRUE(circle->CalculateDamage(hp) == 25);
  ASSERT_TRUE(triangle->CalculateDamage(hp) == 15);
  ASSERT_TRUE(percent->CalculateDamage(hp) == 50);

  simple->update();
  triangle->update();

  ASSERT_TRUE(simple->cond.y > triangle->cond.y);
}
