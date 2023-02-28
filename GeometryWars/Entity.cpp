#include "Entity.h"

Entity::Entity(int id, EntityTag tag) : id_(id), tag_(tag), alive_(true) {}

void Entity::setTransform(std::unique_ptr<CTransform> transform) {
  transform_ = std::move(transform);
}

CTransform* Entity::getTransform() { return transform_.get(); }

void Entity::setCollision(std::unique_ptr<CCollision> collision) {
  collision_ = std::move(collision);
}

CCollision* Entity::getCollision() { return collision_.get(); }

void Entity::setShape(std::unique_ptr<CShape> shape) {
  shape_ = std::move(shape);
}

CShape* Entity::getShape() { return shape_.get(); }

void Entity::setScore(std::unique_ptr<CScore> score) {
  score_ = std::move(score);
}

CScore* Entity::getScore() { return score_.get(); }

void Entity::setText(std::unique_ptr<CText> text) { text_ = std::move(text); }

CText* Entity::getText() { return text_.get(); }

int Entity::getId() const { return id_; }

EntityTag Entity::getTag() const { return tag_; }

bool Entity::isAlive() const { return alive_; }

void Entity::destroy() { alive_ = false; }
