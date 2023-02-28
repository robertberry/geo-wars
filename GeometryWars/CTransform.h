#pragma once

#include "Vec2.h"

class CTransform final {
 public:
  CTransform(const Vec2& position, const Vec2& velocity, float angle);

  const Vec2& getPosition() const;
  const Vec2& getVelocity() const;
  float getAngle() const;

  void setAngle(float angle);
  void setPosition(const Vec2& position);
  void setVelocity(const Vec2& velocity);

 private:
  Vec2 position_;
  Vec2 velocity_;
  float angle_;
};
