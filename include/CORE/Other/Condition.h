#pragma once
struct Point {
  float x;
  float y;

  Point() = default;
  Point(float x, float y);
};

struct Condition {
  float x;  // подразумевается левый верхний угол
  float y;
  float height;
  float width;
  float rotation;

  Condition(float x, float y, float height, float width, float rotation = 0);
  Condition() = default;
  void move(float x_ch, float y_ch);
  void move(const Point& point);
  void setPosition(float x_ch, float y_ch);
  void setPosition(const Point& point);
  void rotate(float degree);
  void setRotation(float degree);
  bool containsPoint(const Point& pnt);
  Condition& operator+=(const Point& point);
  Point point();
};

bool checkInterfere(const Condition& first, const Condition& second);
