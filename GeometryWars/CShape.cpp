#include "CShape.h"

#include "SFML/Graphics.hpp"

CShape::CShape(float radius, int points, const sf::Color& fill,
               const sf::Color& outline, float thickness)
    : radius_(radius), circle_() {
  circle_.setRadius(radius);
  circle_.setPointCount(points);
  circle_.setFillColor(fill);
  circle_.setOutlineColor(outline);
  circle_.setOutlineThickness(thickness);
  circle_.setOrigin(sf::Vector2f(/*X=*/radius, /*Y=*/radius));
}

sf::CircleShape& CShape::getCircle() { return circle_; }

float CShape::getRadius() { return radius_; }
