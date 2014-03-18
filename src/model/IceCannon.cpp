#include "IceCannon.h"

IceCannon::IceCannon(FloatRect* boundPtr, const int& attackDamage, const int& range, const float& attackDelay,
                    const float& rotation, const float& rotationSpeed, const int& blastRadius,
                    const float& slowEffectPercentage) :
SplashCannon(boundPtr, attackDamage, range, attackDelay, rotation, rotationSpeed, blastRadius), slowEffectPercentage(slowEffectPercentage) {
    //ctor
}

IceCannon::~IceCannon() {
    //dtor
}
