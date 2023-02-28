#pragma once

#include <memory>

#include "CCollision.h"
#include "CScore.h"
#include "CShape.h"
#include "CText.h"
#include "CTransform.h"

typedef size_t EntityTag;

constexpr EntityTag TAG_PLAYER = 0;
constexpr EntityTag TAG_ENEMY = 1;
constexpr EntityTag TAG_BULLET = 2;
constexpr EntityTag TAG_CHROME = 3;

class Entity final {
 public:
  friend class EntityManager;

  void setTransform(std::unique_ptr<CTransform> transform);
  CTransform* getTransform();

  void setCollision(std::unique_ptr<CCollision> collision);
  CCollision* getCollision();

  void setShape(std::unique_ptr<CShape> shape);
  CShape* getShape();

  void setScore(std::unique_ptr<CScore> score);
  CScore* getScore();

  void setText(std::unique_ptr<CText> text);
  CText* getText();

  int getId() const;
  EntityTag getTag() const;

  bool isAlive() const;

  void destroy();

 private:
  int id_;
  bool alive_;
  EntityTag tag_;

  std::unique_ptr<CTransform> transform_;
  std::unique_ptr<CCollision> collision_;
  std::unique_ptr<CShape> shape_;
  std::unique_ptr<CScore> score_;
  std::unique_ptr<CText> text_;

  Entity(int id, EntityTag tag);
};
