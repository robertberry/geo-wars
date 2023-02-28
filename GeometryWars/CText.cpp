#include "CText.h"

CText::CText(const std::string& text, sf::Font& font, int character_size,
             sf::Color color)
    : renderable_text_() {
  renderable_text_.setString(text);
  renderable_text_.setCharacterSize(character_size);
  renderable_text_.setFont(font);
  renderable_text_.setFillColor(color);
  renderable_text_.setStyle(sf::Text::Regular);
}

void CText::setString(const std::string& text) {
  renderable_text_.setString(text);
}

sf::Text& CText::getText() { return renderable_text_; }
