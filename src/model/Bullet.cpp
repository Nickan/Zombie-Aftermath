#include "Bullet.h"

Vec2 Bullet::vec2;

Bullet::Bullet(FloatRect* boundPtr, float rotation)
:boundPtr(boundPtr), rotation(rotation) {
    updating = false;
    speed = 100.0f;
    boundAllowance = 5.0f;

    targetRectPtr = NULL;
}

const bool Bullet::targetHit() {
    float centerX = boundPtr->left + (boundPtr->width / 2);
    float centerY = boundPtr->top + (boundPtr->height / 2);

    // If there is a set target
    if (targetRectPtr != NULL) {
        float targetCenterX = targetRectPtr->left + (targetRectPtr->width / 2);
        float targetCenterY = targetRectPtr->top + (targetRectPtr->height / 2);

        vec2.x = targetCenterX - centerX;
        vec2.y = targetCenterY - centerY;
    } else {
        // Target ground
        vec2.x = targetX - centerX;
        vec2.y = targetY - centerY;
    }

    if (vec2.getLengthSqr() < boundAllowance * boundAllowance) {
        targetRectPtr = NULL;
        return true;
    }

    return false;
}

void Bullet::trackTarget(const float& delta) {
    float centerX = boundPtr->left + (boundPtr->width / 2);
    float centerY = boundPtr->top + (boundPtr->height / 2);

    // If there is a set target
    if (targetRectPtr != NULL) {
        float targetCenterX = targetRectPtr->left + (targetRectPtr->width / 2);
        float targetCenterY = targetRectPtr->top + (targetRectPtr->height / 2);

        vec2.x = targetCenterX - centerX;
        vec2.y = targetCenterY - centerY;
    } else {
        // Target ground
        vec2.x = targetX - centerX;
        vec2.y = targetY - centerY;
    }

    vec2.normalize();
    rotation = RotationManager::getDegree(vec2.x, vec2.y);

    boundPtr->left += vec2.x * speed * delta;
    boundPtr->top += vec2.y * speed * delta;
}

void Bullet::setAsCenter(const float& x, const float& y) {
    boundPtr->left = x - boundPtr->width / 2;
    boundPtr->top = y - boundPtr->height / 2;
}

void Bullet::setTarget(FloatRect* targetRect) {
    this->targetRectPtr = targetRect;
}

void Bullet::setTarget(const float& targetX, const float& targetY) {
    this->targetX = targetX;
    this->targetY = targetY;
}

Bullet::~Bullet() {
    //dtor
}
