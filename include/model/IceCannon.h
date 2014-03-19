#ifndef ICECANNON_H
#define ICECANNON_H

#include "SplashCannon.h"

class IceCannon : public SplashCannon {
    public:
        IceCannon(FloatRect* boundPtr, const int& attackDamage, const int& range, const float& attackDelay,
                    const float& rotation, const float& rotationSpeed, const int& blastRadius,
                    const float& slowEffectPercentage);
        virtual ~IceCannon();

        void setBulletTarget(Bullet* bulletPtr);

        float slowEffectPercentage;
    protected:
    private:
};

#endif // ICECANNON_H
