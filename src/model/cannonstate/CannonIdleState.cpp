#include "CannonIdleState.h"

CannonIdleState CannonIdleState::instance;

CannonIdleState::CannonIdleState() {
    //ctor
}

void CannonIdleState::start(Cannon* cannonPtr) {
    cannonPtr->setTargetId(-1);

}

void CannonIdleState::update(Cannon* canPtr, const float& delta) {

    // Update the remaining release bullet if there are
    const vector<Bullet*>& bullets = canPtr->getBullets();
    for (unsigned int index = 0; index < bullets.size(); ++index) {
        if (bullets.at(index)->updating) {
            canPtr->bulletUpdate(bullets.at(index), delta);
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
