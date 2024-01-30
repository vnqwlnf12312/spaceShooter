#include "CORE/Other/Movement.h"

Linear::Linear(): a(0), b(1) {}
Linear::Linear(float a, float b): a(a), b(b) {}

float ScalarProd(const Point& first, const Point& second) {
  return first.x * second.x + first.y * second.y;
}

Point& normalize(Point& pnt, float len) {
  float cur_len = std::sqrt(ScalarProd(pnt, pnt));
  pnt.x *= (len / cur_len);
  pnt.y *= (len / cur_len);
  return pnt;
}

Point Linear::move(const Point& coords, float speed) {
  Point to_return{a, b};
  return normalize(to_return, speed);
}

Point Parabolic::move(const Point& coords, float speed) {
  Point to_return{2 * a * coords.x + b, c - a * coords.x * coords.x};
  normalize(to_return, speed);
  return to_return;
}
