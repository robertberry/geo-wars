#include "RandomCountdown.h"

RandomCountdown::RandomCountdown(int minMillis, int maxMillis)
    : min_millis_(minMillis), max_millis_(maxMillis), millis_remaining_(0) {}

void RandomCountdown::update(sf::Time time) {
  millis_remaining_ -= time.asMilliseconds();
}

bool RandomCountdown::isFinished() { return millis_remaining_ <= 0; }

void RandomCountdown::reset() {
  millis_remaining_ = (rand() % (max_millis_ - min_millis_)) + min_millis_;
}
