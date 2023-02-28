#pragma once

class CCollision final {
 public:
  CCollision(float radius);

  float getRadius();

 private:
  float radius_;
};
