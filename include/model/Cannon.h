#ifndef CANNON_H
#define CANNON_H

#include <vector>

#include "Bullet.h"
#include "Entity.h"

using namespace std;

class Cannon : public Entity {
    public:
        Cannon(FloatRect* boundPtr, int attackDamage, int range, float attackDelay, float rotation, float rotationSpeed);

        int attackDamage;
        int range;

        float attackDelay;
        float rotationSpeed;

        vector<Bullet*>* bulletsPtr;

        virtual ~Cannon();
    protected:
    private:
        float attackTimer;
};

#endif // CANNON_H
