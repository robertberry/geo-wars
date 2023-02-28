#include "GameInput.h"

GameInput::GameInput()
    : is_up_pressed_(false),
      is_down_pressed_(false),
      is_left_pressed_(false),
      is_right_pressed_(false),
      last_left_click_position_(0, 0),
      is_left_click_pending_(false) {}

bool GameInput::isUp() { return is_up_pressed_; }

bool GameInput::isDown() { return is_down_pressed_; }

bool GameInput::isLeft() { return is_left_pressed_; }

bool GameInput::isRight() { return is_right_pressed_; }

Vec2& GameInput::lastLeftClickPosition() { return last_left_click_position_; }

bool GameInput::isLeftClickPending() { return is_left_click_pending_; }

void GameInput::onEvent(const sf::Event& ev) {
  if (ev.type == sf::Event::KeyPressed) {
    switch (ev.key.code) {
      case sf::Keyboard::Up:
      case sf::Keyboard::W:
        is_up_pressed_ = true;
        break;
      case sf::Keyboard::Down:
      case sf::Keyboard::S:
        is_down_pressed_ = true;
        break;
      case sf::Keyboard::Left:
      case sf::Keyboard::A:
        is_left_pressed_ = true;
        break;
      case sf::Keyboard::Right:
      case sf::Keyboard::D:
        is_right_pressed_ = true;
        break;
    }
  } else if (ev.type == sf::Event::KeyReleased) {
    switch (ev.key.code) {
      case sf::Keyboard::Up:
      case sf::Keyboard::W:
        is_up_pressed_ = false;
        break;
      case sf::Keyboard::Down:
      case sf::Keyboard::S:
        is_down_pressed_ = false;
        break;
      case sf::Keyboard::Left:
      case sf::Keyboard::A:
        is_left_pressed_ = false;
        break;
      case sf::Keyboard::Right:
      case sf::Keyboard::D:
        is_right_pressed_ = false;
        break;
    }
  } else if (ev.type == sf::Event::MouseButtonPressed) {
    if (ev.mouseButton.button == sf::Mouse::Left) {
      last_left_click_position_ = Vec2(ev.mouseButton.x, ev.mouseButton.y);
      is_left_click_pending_ = true;
    }
  }
}

void GameInput::resetIsLeftClickPending() { is_left_click_pending_ = false; }
