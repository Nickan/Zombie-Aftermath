#include "IceCannon.h"

IceCannon::IceCannon(FloatRect* boundPtr, const int& attackDamage, const int& range, const float& attackDelay,
                    const float& rotation, const float& rotationSpeed, const int& blastRadius,
                    const float& slowEffectPercentage) :
SplashCannon(boundPtr, attackDamage, range, attackDelay, rotation, rotationSpeed, blastRadius) {
    //ctor
}

void IceCannon::setBulletTarget(Bullet* bulletPtr) {
    bulletPtr->setTarget(targetRectPtr->left + (targetRectPtr->width / 2), targetRectPtr->top + (targetRectPtr->height / 2));
}

void IceCannon::bulletHit(Bullet* bulPtr) {

}

IceCannon::~IceCannon() {
    //dtor
}
