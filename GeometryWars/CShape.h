#pragma once

#include "SFML/Graphics.hpp"

class CShape final {
 public:
  CShape(float radius, int points, const sf::Color& fill,
         const sf::Color& outline, float thickness);

  sf::CircleShape& getCircle();

  float getRadius();

 private:
  float radius_;
  sf::CircleShape circle_;
};
