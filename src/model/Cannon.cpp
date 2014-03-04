#include "Cannon.h"

Cannon::Cannon(FloatRect* boundPtr, int attackDamage, int range, float attackDelay,
                float rotation, float rotationSpeed)
: Entity(boundPtr, rotation), attackDamage(attackDamage), range(range),
attackDelay(attackDelay), rotationSpeed(rotationSpeed)
{
    //ctor
}

Cannon::~Cannon() {
    for (unsigned int index = 0; index < bulletsPtr->size(); ++index) {
        delete bulletsPtr->at(index);
    }

    delete bulletsPtr;
}
