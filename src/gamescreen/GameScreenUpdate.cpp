#include "GameScreenUpdate.h"

GameScreenUpdate::GameScreenUpdate() {
    mapPos.x = 0;
    mapPos.y = 0;

    zomSpawnManagerPtr = NULL;

    float width = 32;
    float height = 32;
    float rotation = 0;
    float speed = 0;
}

void GameScreenUpdate::initializeMapInfo(const vector<vector<float> >& tileMapInfo) {
    pathFinderPtr = new AStarPathfinder(50, 38);
    pathFinderPtr->diagonalMoveEnable = false;       //-> Diagonal movement is still not tested

    tileStatus = tileMapInfo;

    for (unsigned int y = 0; y < tileMapInfo.size(); ++y) {
        for (unsigned int x = 0; x < tileMapInfo.at(y).size(); ++x) {
            // The tile is not walkable
            if (tileMapInfo.at(y).at(x) == 0) {
                pathFinderPtr->setNodeType(x, y, NodeType::UNWALKABLE);
            }
        }
    }
    zomTarDistPtr = new Vector2i(24, 23);

    // Initialize the path list
    path6_0 = pathFinderPtr->getPath(6, 0, zomTarDistPtr->x, zomTarDistPtr->y);
    path14_0 = pathFinderPtr->getPath(14, 0, zomTarDistPtr->x, zomTarDistPtr->y);
    path21_0 = pathFinderPtr->getPath(21, 0, zomTarDistPtr->x, zomTarDistPtr->y);
	path29_0 = pathFinderPtr->getPath(29, 0, zomTarDistPtr->x, zomTarDistPtr->y);
	path36_0 = pathFinderPtr->getPath(36, 0, zomTarDistPtr->x, zomTarDistPtr->y);
	path44_0 = pathFinderPtr->getPath(44, 0, zomTarDistPtr->x, zomTarDistPtr->y);
	path49_8 = pathFinderPtr->getPath(49, 8, zomTarDistPtr->x, zomTarDistPtr->y);
	path0_8 = pathFinderPtr->getPath(0, 8, zomTarDistPtr->x, zomTarDistPtr->y);
	path0_23 = pathFinderPtr->getPath(0, 23, zomTarDistPtr->x, zomTarDistPtr->y);
	path49_23 = pathFinderPtr->getPath(49, 23, zomTarDistPtr->x, zomTarDistPtr->y);

    initializeZombieVariables();

    zomSpawnManagerPtr = new ZombieSpawnManager();
}

void GameScreenUpdate::initializeZombieVariables() {
    //...
    cout << "Path list: " << endl;
    for (unsigned int index = 0; index < path6_0.size(); ++index) {
        cout << path6_0.at(index)->x << ": " << path6_0.at(index)->y << endl;
    }
}

void GameScreenUpdate::update(const float& delta) {
    if (zomSpawnManagerPtr != NULL) {
        if (zomSpawnManagerPtr->spawnZombie(delta)) {
            spawnZombie(zomSpawnManagerPtr->totalSpawn);
        }
    }

    for (unsigned int index = 0; index < zomPtrs.size(); ++index) {
        if (zomPtrs.at(index)->getLife() > 0) {
            zomPtrs.at(index)->update(delta);
        }
    }

    updateNormalCannon(delta);
    updateSplashCannon(delta);
    updateIceCannon(delta);
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

                // Zombie in range
                if (zombieInRange(canPtr->boundPtr, zomBoundPtr, canPtr->range) ) {
                    canPtr->setTargetId(zomPtrs.at(zomIndex)->getId());
                }

            }
        }

        canPtr->update(delta);
    }
}

void GameScreenUpdate::updateIceCannon(const float& delta) {
    for (unsigned int index = 0; index < iceCanPtrs.size(); ++index) {
        IceCannon* canPtr = iceCanPtrs.at(index);

        // Check if the cannon doesn't have any target
        if (canPtr->getTargetId() == -1) {
            // Check if there is zombie in range
            for (unsigned int zomIndex = 0; zomIndex < zomPtrs.size(); ++zomIndex) {
                FloatRect* zomBoundPtr = zomPtrs.at(zomIndex)->boundPtr;

                // If the zombie is dead, continue to the next zombie
                if (zomPtrs.at(zomIndex)->getLife() <= 0) {
                    continue;
                }

                // Zombie in range
                if (zombieInRange(canPtr->boundPtr, zomBoundPtr, canPtr->range) ) {
                    canPtr->setTargetId(zomPtrs.at(zomIndex)->getId());
                }

            }
        }

        canPtr->update(delta);
    }
}

void GameScreenUpdate::updateSplashCannon(const float& delta) {
    for (unsigned int index = 0; index < splashCanPtrs.size(); ++index) {
        SplashCannon* canPtr = splashCanPtrs.at(index);

        // Check if the cannon doesn't have any target
        if (canPtr->getTargetId() == -1) {
            // Check if there is zombie in range
            for (unsigned int zomIndex = 0; zomIndex < zomPtrs.size(); ++zomIndex) {
                FloatRect* zomBoundPtr = zomPtrs.at(zomIndex)->boundPtr;

                // If the zombie is dead, continue to the next zombie
                if (zomPtrs.at(zomIndex)->getLife() <= 0) {
                    continue;
                }

                // Zombie in range
                if (zombieInRange(canPtr->boundPtr, zomBoundPtr, canPtr->range) ) {
                    canPtr->setTargetId(zomPtrs.at(zomIndex)->getId());
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

            cout << "Set to be deleted zombie index: " << index << endl;
            break;
        }
    }
}


//-------------------- Helper functions ------------------
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

void GameScreenUpdate::spawnZombie(const int& spawnAreaNumber) {
    Zombie* newZom;
    float speed = 16;
    float rotation = 0;
    float width = 32;
    float height = 32;
    switch (spawnAreaNumber % 10) {
    case 0: newZom = new Zombie(new FloatRect(32 * 6, 0, width, height), rotation, speed);
            newZom->setPath(path6_0);
        break;
    case 1: newZom = new Zombie(new FloatRect(32 * 14, 0, width, height), rotation, speed);
            newZom->setPath(path14_0);
        break;
    case 2: newZom = new Zombie(new FloatRect(32 * 21, 0, width, height), rotation, speed);
            newZom->setPath(path21_0);
        break;
    case 3: newZom = new Zombie(new FloatRect(32 * 29, 0, width, height), rotation, speed);
            newZom->setPath(path29_0);
        break;
    case 4: newZom = new Zombie(new FloatRect(32 * 36, 0, width, height), rotation, speed);
            newZom->setPath(path36_0);
        break;
    case 5: newZom = new Zombie(new FloatRect(32 * 44, 0, width, height), rotation, speed);
            newZom->setPath(path44_0);
        break;
    case 6: newZom = new Zombie(new FloatRect(32 * 49, 32 * 8, width, height), rotation, speed);
            newZom->setPath(path49_8);
        break;
    case 7: newZom = new Zombie(new FloatRect(32 * 0, 32 * 8, width, height), rotation, speed);
            newZom->setPath(path0_8);
        break;
    case 8: newZom = new Zombie(new FloatRect(32 * 0, 32 * 23, width, height), rotation, speed);
            newZom->setPath(path0_23);
        break;
    case 9: newZom = new Zombie(new FloatRect(32 * 49, 32 * 23, width, height), rotation, speed);
            newZom->setPath(path49_23);
        break;
    default:
        break;
    }
    zomPtrs.push_back(newZom);
}


//--------------------- Setters --------------------------
void GameScreenUpdate::createCannon(const string& canName, const int& tileX, const int& tileY) {
    int attackDamage = 10;
    int range = 96;
    float attackDelay = 1.0f;
    float rotation = 0;
    float rotationSpeed = 50.0f;

    if (canName == "normalcannon") {
        norCanPtrs.push_back(new Cannon(new FloatRect(tileX * 32, tileY * 32, 32, 32), attackDamage,
                                range, attackDelay, rotation, rotationSpeed));
    }

    int blastRadius = 64;
    if (canName == "icecannon") {
        float slowEffectPercentage = 50.0f;
        iceCanPtrs.push_back(new IceCannon(new FloatRect(tileX * 32, tileY * 32, 32, 32), attackDamage,
                                range, attackDelay, rotation, rotationSpeed, blastRadius, slowEffectPercentage));
    }

    if (canName == "splashcannon") {
        splashCanPtrs.push_back(new SplashCannon(new FloatRect(tileX * 32, tileY * 32, 32, 32), attackDamage,
                                range, attackDelay, rotation, rotationSpeed, blastRadius));
    }
}


//--------------------- Getters --------------------------
const vector<Zombie*>& GameScreenUpdate::getZombiePtrs() {
    return zomPtrs;
}

const vector<Cannon*>& GameScreenUpdate::getNorCanPtrs() {
    return norCanPtrs;
}

const vector<IceCannon*>& GameScreenUpdate::getIceCanPtrs() {
    return iceCanPtrs;
}

const vector<SplashCannon*>& GameScreenUpdate::getSplCanPtrs() {
    return splashCanPtrs;
}

GameScreenUpdate::~GameScreenUpdate() {
    delete pathFinderPtr;
    delete zomTarDistPtr;
    delete zomSpawnManagerPtr;

    for (unsigned int index = 0; index < zomPtrs.size(); ++index) {
        delete zomPtrs.at(index);
    }
}
