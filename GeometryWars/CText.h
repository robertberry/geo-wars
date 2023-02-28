#pragma once

#include <memory>
#include <string>

#include "SFML/Graphics.hpp"

class CText final {
 public:
  CText(const std::string& text, sf::Font& font, int character_size,
        sf::Color color);

  void setString(const std::string& text);
  sf::Text& getText();

 private:
  sf::Text renderable_text_;
};
