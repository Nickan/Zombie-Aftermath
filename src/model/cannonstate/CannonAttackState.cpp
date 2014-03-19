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

        // Check if the zombie is still alive before setting up bullet
        Zombie* tarZomPtr = (Zombie*) EntityManager::getEntity(canPtr->getTargetId());

        // If the target exist
        if (tarZomPtr != NULL) {

            // Alive
            if (tarZomPtr->getLife() > 0) {

                // Set the attack timer, if the attack delay is reached, set a bullet to attack the zombie
                canPtr->attackTimer += delta;
                if (canPtr->attackTimer >= canPtr->attackDelay) {
                    // Reset the attack timer
                    canPtr->attackTimer -= canPtr->attackDelay;

                    // Get an available bullet to attack the zombie
                    Bullet* bulPtr = canPtr->getAvailableBullet();
                    canPtr->placeOnTurret(bulPtr);
                    canPtr->setBulletTarget(bulPtr);
                }

            } else {
                // Already dead
                canPtr->setIdle();
            }
        } else {
            // The target doesn't exist or killed by other cannon
            canPtr->setIdle();
        }

        // If the target gets out of range
        if (!canPtr->zombieInRange()) {
            canPtr->setIdle();
        }

    }

    // Even if the cannon has not locked on to the target yet, update the released bullet
    const vector<Bullet*>& bullets = canPtr->getBullets();
    for (unsigned int index = 0; index < bullets.size(); ++index) {
        Bullet* bulPtr = bullets.at(index);

        // Bullet is set to be fired
        if (bulPtr->isFired()) {

            // Only update the bullet when set to fire
            bulPtr->update(delta);

            // Check if the target is hit, it automatically set the fire to false if already hit the target
            if (bulPtr->isTargetHit()) {
                canPtr->bulletHit(bulPtr);
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
