#pragma once

#include <memory>

#include "SFML/Graphics.hpp"
#include "Vec2.h"

class GameInput final {
 public:
  GameInput();

  bool isUp();
  bool isDown();
  bool isLeft();
  bool isRight();
  Vec2& lastLeftClickPosition();
  bool isLeftClickPending();

  void onEvent(const sf::Event& ev);
  void resetIsLeftClickPending();

  GameInput(const GameInput&) = delete;
  GameInput& operator=(const GameInput&) = delete;

 private:
  bool is_up_pressed_;
  bool is_down_pressed_;
  bool is_left_pressed_;
  bool is_right_pressed_;
  bool is_left_click_pending_;
  Vec2 last_left_click_position_;
};
