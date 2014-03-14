#include "Bullet.h"

Vec2 Bullet::vec2;

Bullet::Bullet(FloatRect* boundPtr, float rotation)
:boundPtr(boundPtr), rotation(rotation) {
    updating = false;
    speed = 100.0f;
    boundAllowance = 5.0f;
}

const bool Bullet::targetHit(const float& targetX, const float& targetY) {
    vec2.x = targetX - boundPtr->left - (boundPtr->width / 2);
    vec2.y = targetY - boundPtr->top - (boundPtr->height / 2);

    return (vec2.getLengthSqr() < boundAllowance * boundAllowance) ? true : false;
}

void Bullet::trackTarget(const float& targetX, const float& targetY, const float& delta) {
    vec2.x = targetX - boundPtr->left - (boundPtr->width / 2);
    vec2.y = targetY - boundPtr->top - (boundPtr->height / 2);
    vec2.normalize();
    rotation = RotationManager::getDegree(vec2.x, vec2.y);

    boundPtr->left += vec2.x * speed * delta;
    boundPtr->top += vec2.y * speed * delta;
}



Bullet::~Bullet() {
    //dtor
}
