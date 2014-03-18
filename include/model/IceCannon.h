#ifndef ICECANNON_H
#define ICECANNON_H

#include "SplashCannon.h"

class IceCannon : public SplashCannon {
    public:
        IceCannon(FloatRect* boundPtr, const int& attackDamage, const int& range, const float& attackDelay,
                    const float& rotation, const float& rotationSpeed, const int& blastRadius,
                    const float& slowEffectPercentage);
        virtual ~IceCannon();

        // Be called after the bullet is set to be fired, where should the bullet set its target
        virtual void setBulletTarget(Bullet* bulletPtr);

        virtual void bulletHit(Bullet* bulPtr);

        float slowEffectPercentage;
    protected:
    private:
};

#endif // ICECANNON_H
