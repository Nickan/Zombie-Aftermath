#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics/Rect.hpp>
#include "Vec2.h"
#include "RotationManager.h"

//---------------------------------------------
//
// Tracks the registered coordinates given
//---------------------------------------------

#include <iostream>
using namespace std;

using namespace sf;

class Bullet {
    public:
        Bullet(FloatRect* boundPtr, float rotation);
        virtual ~Bullet();

        void update(const float& delta);

        // Setting center position
        void setAsCenter(const float& x, const float& y);

        void setTarget(FloatRect* targetRect);
        void setTarget(const float& targetX, const float& targetY);

        // Returns whether it hits the target
        const bool& isTargetHit();
        const bool& isFired();

        // Switches to false every call to assure that will only return true once when
        // set to true every bullet hit the target
        const bool playExplosionAnimation();

        FloatRect* boundPtr;
        float rotation;
        float speed;

        float boundAllowance;

        int targetId;

    protected:
    private:
        void trackTarget(const float& delta);

        const float getDistFromTarget();

        static Vec2 vec2;

        bool fired;
        bool targetHit;

        // Exclusively for playing explosion
        bool playExplosion;

        // The target is only coordinates on the map
        float targetX;
        float targetY;

        // The target is an entity
        FloatRect* targetRectPtr;
};

#endif // BULLET_H
