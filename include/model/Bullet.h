#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics/Rect.hpp>
#include "Vec2.h"
#include "RotationManager.h"

//...
#include <iostream>
using namespace std;

using namespace sf;

class Bullet {
    public:
        Bullet(FloatRect* boundPtr, float rotation);
        virtual ~Bullet();

        // Returns whether it hits the target
        const bool targetHit(const float& targetX, const float& targetY);


        void trackTarget(const float& targetX, const float& targetY, const float& delta);

        FloatRect* boundPtr;
        float rotation;
        float speed;

        bool updating;
        float boundAllowance;
    protected:
    private:
        static Vec2 vec2;
};

#endif // BULLET_H
