#include "CannonIdleState.h"

CannonIdleState CannonIdleState::instance;

CannonIdleState::CannonIdleState() {
    //ctor
}

void CannonIdleState::start(Cannon* cannonPtr) {
    cannonPtr->setTargetId(-1);
    //...
    cout << "Idle" << endl << endl;
}

void CannonIdleState::update(Cannon* canPtr, const float& delta) {
    // Even if the cannon has not locked on to the target yet, update the released bullet
    const vector<Bullet*>& bullets = canPtr->getBullets();
    for (unsigned int index = 0; index < bullets.size(); ++index) {
        Bullet* bulPtr = bullets.at(index);

        // Bullet is set to be fired
        if (bulPtr->isFired()) {

            // Track the set target
            bulPtr->trackTarget(delta);

            // Check if the target is hit, it automatically set the fire to false if already hit the target
            if (bulPtr->targetHit()) {
                canPtr->bulletHit(bulPtr);
            }

        }
    }
}

void CannonIdleState::exit(Cannon* cannonPtr) {

}

CannonIdleState* CannonIdleState::getInstance() {
    return &instance;
}

CannonIdleState::~CannonIdleState() {
    //dtor
}
