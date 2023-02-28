#include "CTransform.h"

CTransform::CTransform(const Vec2& position, const Vec2& velocity, float angle)
    : position_(position), velocity_(velocity), angle_(angle) {}

const Vec2& CTransform::getPosition() const { return position_; }

const Vec2& CTransform::getVelocity() const { return velocity_; }

float CTransform::getAngle() const { return angle_; }

void CTransform::setAngle(float angle) { angle_ = angle; }

void CTransform::setPosition(const Vec2& position) { position_ = position; }

void CTransform::setVelocity(const Vec2& velocity) { velocity_ = velocity; }
