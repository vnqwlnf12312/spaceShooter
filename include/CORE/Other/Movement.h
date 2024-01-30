#include <cmath>

#include "CORE/Other/Condition.h"

#pragma once

class Move {
 public:
  virtual Point move(const Point& coords, float speed) = 0;
};

class Linear : public Move {
  float a, b;

 public:
  Linear();
  Linear(float a, float b);
  Point move(const Point& coords, float speed) override;
};

class Parabolic : public Move {
  float a;
  float b;
  float c;

 public:
  Parabolic() : a(1), b(1), c(1) {}
  Parabolic(float a, float b, float c) : a(a), b(b), c(c) {}
  Point move(const Point& coords, float speed) override;
};

float ScalarProd(const Point& first, const Point& other);
Point& normalize(Point& vec, float len);
