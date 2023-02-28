#pragma once

#include "SFML/Graphics.hpp"

class RandomCountdown final {
 public:
  RandomCountdown(int minMillis, int maxMillis);
  void update(sf::Time time);
  bool isFinished();
  void reset();

 private:
  int min_millis_;
  int max_millis_;
  int millis_remaining_;
};