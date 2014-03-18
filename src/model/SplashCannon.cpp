#include "SplashCannon.h"

SplashCannon::SplashCannon(FloatRect* boundPtr, const int& attackDamage, const int& range, const float& attackDelay,
                    const float& rotation, const float& rotationSpeed, const int& blastRadius) :
Cannon(boundPtr, attackDamage, range, attackDelay, rotation, rotationSpeed), blastRadius(blastRadius) {

}

void SplashCannon::setBulletTarget(Bullet* bulletPtr) {
    bulletPtr->setTarget(targetRectPtr->left + (targetRectPtr->width / 2), targetRectPtr->top + (targetRectPtr->height / 2));
}

void SplashCannon::bulletHit(Bullet* bulPtr) {

}

SplashCannon::~SplashCannon() {
    //dtor
}
