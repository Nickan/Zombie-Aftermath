#include "SplashCannon.h"

SplashCannon::SplashCannon(FloatRect* boundPtr, const int& attackDamage, const int& range, const float& attackDelay,
                    const float& rotation, const float& rotationSpeed, const int& blastRadius) :
Cannon(boundPtr, attackDamage, range, attackDelay, rotation, rotationSpeed), blastRadius(blastRadius) {
    groundHit = false;
}

void SplashCannon::setBulletTarget(Bullet* bulletPtr) {
    bulletPtr->setTarget(targetRectPtr->left + (targetRectPtr->width / 2), targetRectPtr->top + (targetRectPtr->height / 2));
}

void SplashCannon::bulletHit(Bullet* bulPtr) {
    groundHit = true;
    bulletBlastPos.x = bulPtr->boundPtr->left + bulPtr->boundPtr->width / 2;
    bulletBlastPos.y = bulPtr->boundPtr->top + bulPtr->boundPtr->height / 2;
}

const bool SplashCannon::hasHitTheGround() {
    // Set it to false when already read as true
    if (groundHit) {
        groundHit = false;
        return true;
    }
    return false;
}

const Vector2i& SplashCannon::getBulletBlastPos() {
    return bulletBlastPos;
}

SplashCannon::~SplashCannon() {
    //dtor
}
