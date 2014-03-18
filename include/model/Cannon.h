#ifndef CANNON_H
#define CANNON_H

#include <vector>

#include "Bullet.h"
#include "Entity.h"
#include "StateMachine.h"

#include "CannonIdleState.h"
#include "CannonAttackState.h"
#include "MessageDispatcher.h"
#include "Vec2.h"

#include <SFML/System/Vector2.hpp>

//...
#include <iostream>

using namespace std;

class Cannon : public Entity {
    public:
        Cannon(FloatRect* boundPtr, const int& attackDamage, const int& range, const float& attackDelay,
                    const float& rotation, const float& rotationSpeed);

        void update(const float& delta);

        // Fires bullet when the target is locked on
        void fireBullet();

        // Be called after the bullet is set to be fired, set the bullet's target
        virtual void setBulletTarget(Bullet* bulletPtr);

        // Update for the bullet
        void bulletUpdate(Bullet* bulPtr, const float& delta);

        virtual void bulletHit(Bullet* bulPtr);

        void setIdle();

        const bool handleMessage(Message* msgPtr);
        const bool targetLocked(const float& delta);
        const bool zombieInRange();

        // Setter
        void setTargetId(const int& id);

        // Getter
        const int& getTargetId();
        const FloatRect* getTargetRect();
        const vector<Bullet*>& getBullets();

        int attackDamage;
        int range;

        float attackTimer;

        float attackDelay;
        float rotationSpeed;


        virtual ~Cannon();
    protected:
        int targetId;
        StateMachine<Cannon>* stateMachinePtr;
        FloatRect* targetRectPtr;
        vector<Bullet*> bulletPtrs;
        static Vec2 vec2;
    private:
        void placeOnTurret(Bullet* bulletPtr);

};

#endif // CANNON_H
