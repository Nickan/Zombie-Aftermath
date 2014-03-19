#include "Bullet.h"

Vec2 Bullet::vec2;

Bullet::Bullet(FloatRect* boundPtr, float rotation)
:boundPtr(boundPtr), rotation(rotation) {
    fired = false;
    speed = 100.0f;
    boundAllowance = 5.0f;

    targetRectPtr = NULL;
}

void Bullet::update(const float& delta) {
    // Don't process anything when not set to be fired
    if (!fired) {
        return;
    }

    trackTarget(delta);

    // Target is hit
    if (getDistFromTarget() < boundAllowance * boundAllowance) {
        fired = false;
        playExplosion = true;
        targetHit = true;
    } else {
        targetHit = false;
    }
}

const float Bullet::getDistFromTarget() {
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

    return vec2.getLengthSqr();
}

const bool& Bullet::isTargetHit() {
    return targetHit;
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
    fired = true;
    this->targetRectPtr = targetRect;
}

void Bullet::setTarget(const float& targetX, const float& targetY) {
    fired = true;
    this->targetX = targetX;
    this->targetY = targetY;
}


const bool& Bullet::isFired() {
    return fired;
}

const bool Bullet::playExplosionAnimation() {
    // Set it to false when detected true, making sure returns true only once per set true
    if (playExplosion) {
        playExplosion = false;
        return true;
    }
    return false;
}

Bullet::~Bullet() {
    //dtor
}
