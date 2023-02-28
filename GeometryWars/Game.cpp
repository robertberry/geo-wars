#include "Game.h"

#include <iostream>
#include <memory>

#include "CShape.h"
#include "SFML/Graphics.hpp"
#include "Vec2.h"

const float kPlayerRadiusPixels = 40.0f;
const float kBulletStartPositionMarginPixels = 10.0f;
const unsigned int kWindowWidth = 1024;
const unsigned int kWindowHeight = 800;
const float kSecondsPerRotation = 1.0f;
const float kDegreesPerFullRotation = 360;
const int kPlayerPixelsPerSecond = 300;
const int kBulletPixelsPerSecond = 1000;
const int kMinDelayEnemySpawnMillis = 1000;
const int kMaxDelayEnemySpawnMillis = 2000;

Game::Game()
    : entity_manager_(),
      window_(sf::VideoMode(kWindowWidth, kWindowHeight), "Geometry Wars"),
      game_input_(),
      random_enemy_generator_(entity_manager_, kWindowWidth, kWindowHeight),
      arial_font_(),
      score_(0),
      score_text_(),
      random_countdown_(kMinDelayEnemySpawnMillis, kMaxDelayEnemySpawnMillis) {
  if (!arial_font_.loadFromFile("fonts/arial.ttf")) {
    std::cerr << "Could not load font" << std::endl;
    exit(1);
  }
}

void Game::run() {
  std::cout << "run()" << std::endl;

  std::cout << "add player" << std::endl;
  addScore();
  addPlayer();

  std::cout << "starting main loop" << std::endl;
  sf::Clock clock;
  while (window_.isOpen()) {
    sf::Time delta = clock.restart();
    random_countdown_.update(delta);
    if (random_countdown_.isFinished()) {
      random_enemy_generator_.spawnEnemy();
      random_countdown_.reset();
    }
    entity_manager_.update();
    sEvents();
    sGameInput();
    sPhysics(delta);
    sDetectCollisions();
    sRender();
  }
}

void Game::sEvents() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_.close();
    }

    game_input_.onEvent(event);
  }
}

void Game::sGameInput() {
  for (Entity* entity : entity_manager_.getEntitiesWithTag(TAG_PLAYER)) {
    CTransform* transform = entity->getTransform();
    if (transform == nullptr) {
      std::cerr << "Unexpected null transform on player" << std::endl;
      return;
    }

    float x_velocity = 0;
    float y_velocity = 0;
    if (game_input_.isDown()) {
      y_velocity = kPlayerPixelsPerSecond;
    } else if (game_input_.isUp()) {
      y_velocity = -kPlayerPixelsPerSecond;
    }
    if (game_input_.isLeft()) {
      x_velocity = -kPlayerPixelsPerSecond;
    } else if (game_input_.isRight()) {
      x_velocity = kPlayerPixelsPerSecond;
    }
    // std::cout << "x_velocity = " << x_velocity << ", y_velocity = " <<
    // y_velocity << std::endl;
    transform->setVelocity(Vec2(x_velocity, y_velocity));

    if (game_input_.isLeftClickPending()) {
      const Vec2& player_position = transform->getPosition();
      Vec2& click_position = game_input_.lastLeftClickPosition();
      Vec2 path = Vec2(click_position.getX() - player_position.getX(),
                       click_position.getY() - player_position.getY())
                      .normalized();
      Vec2 bullet_velocity = path * kBulletPixelsPerSecond;
      Vec2 bullet_start_position =
          player_position +
          path * (kBulletStartPositionMarginPixels + kPlayerRadiusPixels);
      Entity& bullet = entity_manager_.addEntity(TAG_BULLET);
      bullet.setTransform(std::make_unique<CTransform>(
          /*position=*/bullet_start_position,
          /*velocity=*/bullet_velocity,
          /*angle=*/0.0f));
      bullet.setShape(std::make_unique<CShape>(
          /*radius=*/10.0f,
          /*points=*/16,
          /*fill=*/sf::Color::Yellow,
          /*outline=*/sf::Color::Blue,
          /*thickness=*/1.0f));

      game_input_.resetIsLeftClickPending();
    }
  }
}

void Game::sPhysics(const sf::Time& delta) {
  float delta_as_seconds = delta.asSeconds();

  for (std::unique_ptr<Entity>& entity : entity_manager_.getEntities()) {
    CTransform* transform = entity->getTransform();
    if (transform == nullptr) {
      std::cerr << "Unexpected null transform" << std::endl;
      continue;
    }

    // Update position
    const Vec2& position = transform->getPosition();
    const Vec2& velocity = transform->getVelocity();
    Vec2 new_position = position + (velocity * delta_as_seconds);
    transform->setPosition(new_position);

    // Apply rotation
    transform->setAngle(transform->getAngle() + delta_as_seconds *
                                                    kSecondsPerRotation *
                                                    kDegreesPerFullRotation);

    // Update shape to match transform
    CShape* shape = entity->getShape();
    if (shape != nullptr) {
      sf::CircleShape& circle = shape->getCircle();
      circle.setPosition(new_position.getX(), new_position.getY());
      circle.setRotation(transform->getAngle());
    }
    CText* text = entity->getText();
    if (text != nullptr) {
      text->getText().setPosition(new_position.getX(), new_position.getY());
    }
  }
}

void Game::sDetectCollisions() {
  for (std::unique_ptr<Entity>& entity : entity_manager_.getEntities()) {
    CTransform* transform = entity->getTransform();
    CShape* shape = entity->getShape();
    if (transform == nullptr) {
      std::cerr << "Unexpected null transform" << std::endl;
      continue;
    }
    if (shape == nullptr) {
      continue;
    }
    EntityTag tag = entity->getTag();
    const Vec2& new_position = transform->getPosition();

    float radius = shape->getRadius();
    float x = new_position.getX();
    float y = new_position.getY();

    // Check for inter-entity collisions
    if (tag == TAG_PLAYER || tag == TAG_BULLET) {
      for (Entity* enemy : entity_manager_.getEntitiesWithTag(TAG_ENEMY)) {
        Entity* entity_ptr = entity.get();
        if (isCollision(entity_ptr, enemy)) {
          if (tag == TAG_PLAYER) {
            onPlayerDeath(entity_ptr);
          } else if (tag == TAG_BULLET) {
            onEnemyDeath(/*bullet=*/entity_ptr, /*enemy=*/enemy);
          }
        }
      }
    }

    // Check for border collisions
    transform->setPosition(new_position.constrain(
        /*min=*/Vec2(radius, radius),
        /*max=*/Vec2(kWindowWidth - radius, kWindowHeight - radius)));
    bool x_collision = (x - radius < 0 || x + radius > kWindowWidth);
    bool y_collision = (y - radius < 0 || y + radius > kWindowHeight);
    // If an enemy, bounce
    if (tag == TAG_ENEMY && (x_collision || y_collision)) {
      float x_multiplier = x_collision ? -1.0f : 1.0f;
      float y_multiplier = y_collision ? -1.0f : 1.0f;
      const Vec2& velocity = transform->getVelocity();
      transform->setVelocity(
          Vec2(x_multiplier * velocity.getX(), y_multiplier * velocity.getY()));
    }
    // If a bullet, destroy
    if (tag == TAG_BULLET && (x_collision || y_collision)) {
      entity->destroy();
    }
  }
}

void Game::sRender() {
  window_.clear();
  // Higher value entity tags are rendered later.
  size_t max_tag = entity_manager_.getMaxTag();
  for (size_t i = 0; i <= max_tag; i++) {
    std::vector<Entity*>& entities = entity_manager_.getEntitiesWithTag(i);
    for (Entity* entity : entities) {
      CShape* shape = entity->getShape();
      if (shape != nullptr) {
        window_.draw(shape->getCircle());
        continue;
      }
      CText* text = entity->getText();
      if (text != nullptr) {
        window_.draw(text->getText());
      }
    }
  }

  window_.display();
}

void Game::addScore() {
  Entity& entity = entity_manager_.addEntity(TAG_CHROME);
  entity.setText(std::make_unique<CText>(
      "Score: 0", arial_font_, /*character_size=*/24, sf::Color::White));
  entity.setTransform(std::make_unique<CTransform>(
      /*position=*/Vec2(10.0f, 10.0f),
      /*velocity=*/Vec2(0.0f, 0.0f),
      /*angle=*/0.0f));
  score_text_ = &entity;
}

void Game::addPlayer() {
  Entity& entity = entity_manager_.addEntity(TAG_PLAYER);
  entity.setShape(std::make_unique<CShape>(
      /*radius=*/kPlayerRadiusPixels,
      /*points=*/8,
      /*fill=*/sf::Color::Red,
      /*outline=*/sf::Color::Blue,
      /*thickness=*/2.0f));
  entity.setTransform(std::make_unique<CTransform>(
      /*position=*/Vec2(kWindowWidth / 2.0f, kWindowHeight / 2.0f),
      /*velocity=*/Vec2(0.0f, 0.0f),
      /*angle=*/0.0f));
}

bool Game::isCollision(Entity* entity1, Entity* entity2) {
  float combined_width =
      entity1->getShape()->getRadius() + entity2->getShape()->getRadius();
  const Vec2& entity1_position = entity1->getTransform()->getPosition();
  const Vec2& entity2_position = entity2->getTransform()->getPosition();
  Vec2 path = entity2_position - entity1_position;
  return path.getMagnitudeSquared() < combined_width * combined_width;
}

void Game::onPlayerDeath(Entity* player) {
  CTransform* transform = player->getTransform();
  transform->setPosition(Vec2(kWindowWidth / 2, kWindowHeight / 2));
}

void Game::onEnemyDeath(Entity* bullet, Entity* enemy) {
  score_ += 10;
  updateScoreText();
  bullet->destroy();
  enemy->destroy();
}

void Game::updateScoreText() {
  if (score_text_ == nullptr) {
    std::cerr << "Null score text entity" << std::endl;
    exit(1);
  }
  score_text_->getText()->setString("Score: " + std::to_string(score_));
}
