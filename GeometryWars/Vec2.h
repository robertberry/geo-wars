#pragma once

// A floating point Vector in 2D space.
class Vec2 {
 public:
  Vec2(float x, float y);

  bool operator==(const Vec2& rhs) const;
  bool operator!=(const Vec2& rhs) const;
  Vec2 operator*(float magnitude) const;
  Vec2 operator+(const Vec2& rhs) const;
  Vec2 operator-(const Vec2& rhs) const;
  Vec2 normalized() const;
  Vec2 withX(float newX) const;
  Vec2 withY(float newY) const;
  Vec2 constrain(Vec2 min, Vec2 max) const;

  float getMagnitudeSquared() const;
  float getMagnitude() const;
  float getX() const;
  float getY() const;

 private:
  float x_;
  float y_;
};
