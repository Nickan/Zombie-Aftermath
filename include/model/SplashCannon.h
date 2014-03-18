#ifndef SPLASHCANNON_H
#define SPLASHCANNON_H

#include "Cannon.h"

class SplashCannon : public Cannon {
    public:
        SplashCannon(FloatRect* boundPtr, const int& attackDamage, const int& range, const float& attackDelay,
                    const float& rotation, const float& rotationSpeed, const int& blastRadius);
        virtual ~SplashCannon();

        // Be called after the bullet is set to be fired, where should the bullet set its target
        virtual void setBulletTarget(Bullet* bulletPtr);

        virtual void bulletHit(Bullet* bulPtr);

        int blastRadius;
    protected:
    private:
};

#endif // SPLASHCANNON_H
