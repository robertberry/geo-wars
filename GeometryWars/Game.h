#pragma once

#include "EntityManager.h"
#include "GameInput.h"
#include "RandomCountdown.h"
#include "RandomEnemyGenerator.h"
#include "SFML/Graphics.hpp"

class Game final {
 public:
  Game();

  void run();

 private:
  EntityManager entity_manager_;
  sf::RenderWindow window_;
  GameInput game_input_;
  RandomEnemyGenerator random_enemy_generator_;
  RandomCountdown random_countdown_;

  sf::Font arial_font_;
  int score_;
  Entity* score_text_;

  void sEvents();
  void sGameInput();
  void sPhysics(const sf::Time& delta);
  void sDetectCollisions();
  void sRender();

  void addScore();
  void addPlayer();

  bool isCollision(Entity* entity1, Entity* entity2);

  void onPlayerDeath(Entity* player);
  void onEnemyDeath(Entity* bullet, Entity* enemy);

  void updateScoreText();
};
