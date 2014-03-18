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

        // Returns whether it hits the target
        const bool targetHit();

        const bool& isFired();

        void trackTarget(const float& delta);

        void setAsCenter(const float& x, const float& y);

        void setTarget(FloatRect* targetRect);
        void setTarget(const float& targetX, const float& targetY);

        FloatRect* boundPtr;
        float rotation;
        float speed;

        float boundAllowance;

        int targetId;

    protected:
    private:
        static Vec2 vec2;

        bool fired;

        // The target is only coordinates on the map
        float targetX;
        float targetY;

        // The target is an entity
        FloatRect* targetRectPtr;
};

#endif // BULLET_H
