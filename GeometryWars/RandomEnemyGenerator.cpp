#include "RandomEnemyGenerator.h"

#include <cstdlib>
#include <vector>

#include "Vec2.h"

const std::vector<ColorSpec> specs = {{sf::Color::Cyan, sf::Color::Magenta},
                                      {sf::Color::Green, sf::Color::Red},
                                      {sf::Color::White, sf::Color::Yellow}};

RandomEnemyGenerator::RandomEnemyGenerator(EntityManager& entity_manager,
                                           int screen_width, int screen_height)
    : entity_manager_(entity_manager),
      screen_width_(screen_width),
      screen_height_(screen_height) {}

void RandomEnemyGenerator::spawnEnemy() {
  Entity& entity = entity_manager_.addEntity(TAG_ENEMY);
  // TODO(robertberry): Randomize it, baby.
  ColorSpec colorSpec = randColorSpec();
  int radius = randRange(/*minInclusive=*/30, /*maxExclusive=*/51);
  entity.setShape(std::make_unique<CShape>(
      /*radius=*/(float)radius,
      /*points=*/randRange(3, 8),
      /*fill=*/colorSpec.fill,
      /*outline=*/colorSpec.outline,
      /*thickness=*/1.0f));
  int diameter = radius * 2;
  int start_x = randRange(/*minInclusive=*/diameter,
                          /*maxExclusive=*/screen_width_ - diameter + 1);
  int start_y = randRange(/*minInclusive=*/diameter,
                          /*maxExclusive=*/screen_height_ - diameter + 1);

  entity.setTransform(std::make_unique<CTransform>(
      /*position=*/Vec2((float)start_x, (float)start_y),
      /*velocity=*/Vec2(400, 200),
      /*angle=*/0.0f));
}

int RandomEnemyGenerator::randRange(int minInclusive, int maxExclusive) const {
  return (rand() % (maxExclusive - minInclusive)) + minInclusive;
}

ColorSpec RandomEnemyGenerator::randColorSpec() const {
  return specs[randRange(0, specs.size())];
}
