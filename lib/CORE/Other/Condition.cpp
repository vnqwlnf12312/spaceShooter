#include "CORE/Other/Condition.h"

Point::Point(float x, float y): x(x), y(y) {}

Condition::Condition(float x, float y, float height, float width,
                     float rotation)
    : x(x),
      y(y),
      height(height),
      width(width),
      rotation(rotation) {}

void Condition::move(float x_ch, float y_ch) {
  x += x_ch;
  y += y_ch;
}

void Condition::move(const Point& point) {
  move(point.x, point.y);
}

void Condition::setPosition(float x_ch, float y_ch) {
  x = x_ch;
  y = y_ch;
}

void Condition::setPosition(const Point& point) {
  setPosition(point.x, point.y);
}

void Condition::rotate(float degrees) { rotation += degrees; }

void Condition::setRotation(float degrees) { rotation = degrees; }

bool checkInterfere(const Condition& first, const Condition& second) {
  float r1_tlx = first.x;
  float r1_tly = first.y;
  float r2_tlx = second.x;
  float r2_tly = second.y;

  float r1_brx = first.x + first.width;
  float r1_bry = first.y - first.height;
  float r2_brx = second.x + first.width;
  float r2_bry = second.y - second.height;
  return !(first.x + first.width < second.x || second.x + second.width < first.x || first.y + first.height < second.y || second.y + second.height < first.y);

  // return !(r1_brx < r2_tlx || r1_tlx > r2_brx || r1_bry < r2_tly ||
  //         r1_tly > r2_bry);
}

Condition& Condition::operator+=(const Point& point) {
  x += point.x;
  y += point.y;
  return *this;
}

Point Condition::point() {
  return Point{x, y};
}

bool Condition::containsPoint(const Point& pnt) {
  return (x + width > pnt.x && x < pnt.x && y + height > pnt.y && y < pnt.y);
}
