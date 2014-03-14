#include "CannonAttackState.h"

CannonAttackState CannonAttackState::instance;

CannonAttackState::CannonAttackState() {
    //ctor
}


void CannonAttackState::start(Cannon* canPtr) {
    cout << "Attack state" << endl;
}

void CannonAttackState::update(Cannon* canPtr, const float& delta) {
    if (canPtr->targetLocked(delta)) {
        canPtr->attackTimer += delta;

        if (canPtr->attackTimer >= canPtr->attackDelay) {
            canPtr->attackTimer -= canPtr->attackDelay;
            canPtr->fireBullet();
        }

        const vector<Bullet*>& bullets = canPtr->getBullets();
        for (unsigned int index = 0; index < bullets.size(); ++index) {
            if (bullets.at(index)->updating) {
                canPtr->bulletUpdate(bullets.at(index), delta);
            }
        }

    }
}

void CannonAttackState::exit(Cannon* canPtr) {

}


CannonAttackState* CannonAttackState::getInstance() {
    return &instance;
}

CannonAttackState::~CannonAttackState() {
    //dtor
}
