#include "Vec2.h"

#include <SFML/Window/Event.hpp>
#include <cmath>

Vec2::Vec2(float x, float y) : x_(x), y_(y) {}

bool Vec2::operator==(const Vec2& rhs) const {
  return x_ == rhs.x_ && y_ == rhs.y_;
}

bool Vec2::operator!=(const Vec2& rhs) const {
  return x_ != rhs.x_ || y_ != rhs.y_;
}

Vec2 Vec2::operator*(float magnitude) const {
  return Vec2(x_ * magnitude, y_ * magnitude);
}

Vec2 Vec2::operator+(const Vec2& rhs) const {
  return Vec2(x_ + rhs.x_, y_ + rhs.y_);
}

Vec2 Vec2::operator-(const Vec2& rhs) const {
  return Vec2(x_ - rhs.x_, y_ - rhs.y_);
}

Vec2 Vec2::normalized() const {
  float sum = std::abs(x_) + std::abs(y_);
  return Vec2(x_ / sum, y_ / sum);
}

Vec2 Vec2::withX(float newX) const { return Vec2(newX, y_); }

Vec2 Vec2::withY(float newY) const { return Vec2(x_, newY); }

Vec2 Vec2::constrain(Vec2 min, Vec2 max) const {
  return Vec2(std::min(std::max(x_, min.getX()), max.getX()),
              std::min(std::max(y_, min.getY()), max.getY()));
}

float Vec2::getMagnitudeSquared() const { return x_ * x_ + y_ * y_; }

float Vec2::getMagnitude() const { return std::sqrtf(x_ * x_ + y_ * y_); }

float Vec2::getX() const { return x_; }

float Vec2::getY() const { return y_; }
