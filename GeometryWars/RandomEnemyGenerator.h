#pragma once

#include "EntityManager.h"

struct ColorSpec {
  sf::Color outline;
  sf::Color fill;
};

class RandomEnemyGenerator final {
 public:
  RandomEnemyGenerator(EntityManager& entity_manager, int screen_width,
                       int screen_height);

  void spawnEnemy();

 private:
  EntityManager& entity_manager_;
  int screen_width_;
  int screen_height_;

  int randRange(int minInclusive, int maxExclusive) const;
  ColorSpec randColorSpec() const;
};
