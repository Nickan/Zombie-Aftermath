#include "GameScreenUpdate.h"

GameScreenUpdate::GameScreenUpdate() {
    tileInfoPtr = NULL;
    mapPos.x = 0;
    mapPos.y = 0;

    initializeZombieVariables();

    int attackDamage = 10;
    int range = 96;
    float attackDelay = 1.0f;
    float rotation = 0;
    float rotationSpeed = 50.0f;
    norCanPtrs.push_back(new Cannon(new FloatRect(32 * 7, 32 * 2, 32, 32),
                            attackDamage, range, attackDelay, rotation, rotationSpeed));
}

void GameScreenUpdate::initializeZombieVariables() {
    pathFinderPtr = new AStarPathfinder(100, 100);
    pathFinderPtr->diagonalMoveEnable = true;       //-> Diagonal movement is still not tested

    zomTarDistPtr = new Vector2i(24, 23);
    vector<Node*> path = pathFinderPtr->getPath(6, 0, zomTarDistPtr->x, zomTarDistPtr->y);

    //...
    cout << "Path list: " << endl;
    for (unsigned int index = 0; index < path.size(); ++index) {
        cout << path.at(index)->x << ": " << path.at(index)->y << endl;
    }

    Zombie* zomPtr = new Zombie(new FloatRect(32 * 6, 0, 32, 32), 0.0f, 5.0f);
    zomPtr->setPath(path);
    zomPtrs.push_back(zomPtr);
}

void GameScreenUpdate::update(const float& delta) {

    for (unsigned int index = 0; index < zomPtrs.size(); ++index) {
        if (zomPtrs.at(index)->getLife() > 0) {
            zomPtrs.at(index)->update(delta);
        }
    }

    updateNormalCannon(delta);
    MessageDispatcher::update(delta);

    updateModelGcTimer(delta);
    zombieDeletionManager();
}

void GameScreenUpdate::updateNormalCannon(const float& delta) {
    for (unsigned int index = 0; index < norCanPtrs.size(); ++index) {
        Cannon* canPtr = norCanPtrs.at(index);

        // Check if the cannon doesn't have any target
        if (canPtr->getTargetId() == -1) {
            // Check if there is zombie in range
            for (unsigned int zomIndex = 0; zomIndex < zomPtrs.size(); ++zomIndex) {
                FloatRect* zomBoundPtr = zomPtrs.at(zomIndex)->boundPtr;

                // If the zombie is dead, continue to the next zombie
                if (zomPtrs.at(zomIndex)->getLife() <= 0) {
                    continue;
                }

                // If there is zombie detected in range, continue finding for other cannons
                if (zombieInRange(canPtr->boundPtr, zomBoundPtr, canPtr->range) ) {
                    canPtr->setTargetId(zomPtrs.at(zomIndex)->getId());
                    continue;
                }

            }
        }

        canPtr->update(delta);
    }
}

void GameScreenUpdate::updateModelGcTimer(const float& delta) {
    for (unsigned int index = 0; index < modelGcTimerPtrs.size(); ++index) {
        ModelGCTimer* timer = modelGcTimerPtrs.at(index);
        timer->duration -= delta;

        // Delete the timer and the entity
        if (timer->duration <= 0) {
            EntityManager::deleteEntity(timer->getEntityId());
            delete timer;
            modelGcTimerPtrs.erase(modelGcTimerPtrs.begin() + index);

            cout << "Deleted index: " << index << endl;
            break;
        }
    }
}

void GameScreenUpdate::zombieDeletionManager() {
    float timeDeletion = 5.0f;
    for (unsigned int index = 0; index < zomPtrs.size(); ++index) {
        if (zomPtrs.at(index)->getLife() <= 0) {
            modelGcTimerPtrs.push_back(new ModelGCTimer(zomPtrs.at(index)->getId(), timeDeletion));
            zomPtrs.erase(zomPtrs.begin() + index);

            cout << "Delete index: " << index << endl;
            break;
        }
    }
}



const bool GameScreenUpdate::zombieInRange(const FloatRect* canRect, const FloatRect* zomRect, const float& range) {
    float canCenterX = canRect->left + canRect->width / 2;
    float canCenterY = canRect->top + canRect->height / 2;
    float zomCenterX = zomRect->left + zomRect->width / 2;
    float zomCenterY = zomRect->top + zomRect->height / 2;

    return isInRange(canCenterX, canCenterY, zomCenterX, zomCenterY, range);
}

const bool GameScreenUpdate::isInRange(const float& x1, const float& y1, const float& x2, const float& y2, const float& range) {
    float distX = x1 - x2;
    float distY = y1 - y2;
    float distSqr = (distX * distX) + (distY * distY);
    if (distSqr <= (range * range)) {
        return true;
    }
    return false;
}


//--------------------- Getters --------------------------
const vector<Zombie*>& GameScreenUpdate::getZombiePtrs() {
    return zomPtrs;
}

const vector<Cannon*>& GameScreenUpdate::getNorCanPtrs() {
    return norCanPtrs;
}

GameScreenUpdate::~GameScreenUpdate() {
    delete pathFinderPtr;
    delete zomTarDistPtr;

    for (unsigned int index = 0; index < zomPtrs.size(); ++index) {
        delete zomPtrs.at(index);
    }
}
