#include "IceCannon.h"

IceCannon::IceCannon(FloatRect* boundPtr, const int& attackDamage, const int& range, const float& attackDelay,
                    const float& rotation, const float& rotationSpeed, const int& blastRadius,
                    const float& slowEffectPercentage) :
SplashCannon(boundPtr, attackDamage, range, attackDelay, rotation, rotationSpeed, blastRadius), slowEffectPercentage(slowEffectPercentage) {
    //ctor
}

void IceCannon::setBulletTarget(Bullet* bulletPtr) {
    bulletPtr->setTarget(targetRectPtr->left + (targetRectPtr->width / 2), targetRectPtr->top + (targetRectPtr->height / 2));

    Settings::playFireIceCannon();
}

IceCannon::~IceCannon() {
    //dtor
}
