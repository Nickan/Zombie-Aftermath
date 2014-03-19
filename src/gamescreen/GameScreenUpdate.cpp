#include "GameScreenUpdate.h"

GameScreenUpdate::GameScreenUpdate() {
    mapPos.x = 0;
    mapPos.y = 0;

    zomSpawnManagerPtr = NULL;
    gameOver = false;
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
    // Don't process anything if game over
    if (gameOver) {
        return;
    }

    // If the player depletes its life to zero, set to game over
    if (Settings::life < 1) {
        gameOver = true;
    }

    updateZombies(delta);
    updateNormalCannon(delta);
    updateSplashCannon(delta);
    updateIceCannon(delta);
    MessageDispatcher::update(delta);

    updateModelGcTimer(delta);
    zombieDeletionManager();
    updateBulletExplosions(delta);
}

void GameScreenUpdate::updateZombies(const float& delta) {
    if (zomSpawnManagerPtr != NULL) {

        zomSpawnManagerPtr->update(delta);

        // If it returns true, spawn a zombie based on the total spawned zombies
        if (zomSpawnManagerPtr->spawnZombie()) {
            spawnZombie(zomSpawnManagerPtr->getTotalSpawn());
        }

        // Limit of spawned zombies reached
        if (zomSpawnManagerPtr->stoppedSpawning()) {
            // If there is no alive zombie
            if (zomPtrs.empty()) {
                //...
                cout << "Stopped spawning" << endl;
                zomSpawnManagerPtr->incrementStage();
            }
        }

    }

    for (unsigned int index = 0; index < zomPtrs.size(); ++index) {
        // Update if there is life left
        if (zomPtrs.at(index)->getLife() > 0) {
            zomPtrs.at(index)->update(delta);
        }
    }
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

        // Detect if the bullet has hit the ground and need to have explosion playing
        const vector<Bullet*> bulPtrs = canPtr->getBullets();
        for (unsigned int index = 0; index < bulPtrs.size(); ++index) {
            if (bulPtrs.at(index)->playExplosionAnimation()) {
                const FloatRect* rectPtr = bulPtrs.at(index)->boundPtr;
                float centerX = rectPtr->left + (rectPtr->width / 2);
                float centerY = rectPtr->top + (rectPtr->height / 2);

                aniExpTimerPtrs.push_back(new AnimationExplosionTimer(centerX, centerY, 0.3f, ExplosionType::NORMAL));
            }
        }

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

        if (canPtr->hasHitTheGround()) {
            handleIceBulletBlast(canPtr);
        }

        // Detect if the bullet has hit the ground and need to have explosion playing
        const vector<Bullet*> bulPtrs = canPtr->getBullets();
        for (unsigned int index = 0; index < bulPtrs.size(); ++index) {
            if (bulPtrs.at(index)->playExplosionAnimation()) {
                const FloatRect* rectPtr = bulPtrs.at(index)->boundPtr;
                float centerX = rectPtr->left;
                float centerY = rectPtr->top;

                aniExpTimerPtrs.push_back(new AnimationExplosionTimer(centerX, centerY, 0.5f, ExplosionType::ICE));
            }
        }
    }
}

void GameScreenUpdate::handleIceBulletBlast(IceCannon* iceCanPtr) {
    for (unsigned int zomIndex = 0; zomIndex < zomPtrs.size(); ++zomIndex) {
        FloatRect* zomBoundPtr = zomPtrs.at(zomIndex)->boundPtr;

        // If the zombie is dead, continue to the next zombie
        if (zomPtrs.at(zomIndex)->getLife() <= 0) {
            continue;
        }

        const Vector2i& bulletBlastPos = iceCanPtr->getBulletBlastPos();
        float zomCenterX = zomBoundPtr->left + zomBoundPtr->width / 2;
        float zomCenterY = zomBoundPtr->top + zomBoundPtr->height / 2;

        // Detects if the zombie is caught in blast
        if (isInRange(bulletBlastPos.x, bulletBlastPos.y, zomCenterX, zomCenterY, iceCanPtr->blastRadius) ) {
            Zombie* zomPtr = zomPtrs.at(zomIndex);

            // Create a container for the attack damage
            Vector2i* atkDmgAndSlowPtr = new Vector2i(iceCanPtr->attackDamage, iceCanPtr->slowEffectPercentage);
            MessageDispatcher::sendMessage(iceCanPtr->getId(), zomPtr->getId(), 0, MessageType::FROZEN, atkDmgAndSlowPtr);
        }
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

        // Detects near zombies and send their are being hit by the bullet's explosion
        if (canPtr->hasHitTheGround()) {
            handleSplashBulletBlast(canPtr);
        }

        // Detect if the bullet has hit the ground and need to have explosion playing
        const vector<Bullet*> bulPtrs = canPtr->getBullets();
        for (unsigned int index = 0; index < bulPtrs.size(); ++index) {
            if (bulPtrs.at(index)->playExplosionAnimation()) {
                const FloatRect* rectPtr = bulPtrs.at(index)->boundPtr;

                float centerX = rectPtr->left + (rectPtr->width / 2);
                float centerY = rectPtr->top + (rectPtr->height / 2);

                aniExpTimerPtrs.push_back(new AnimationExplosionTimer(centerX, centerY, 0.5f, ExplosionType::SPLASH));
            }
        }

    }
}

void GameScreenUpdate::handleSplashBulletBlast(SplashCannon* splCanPtr) {
    for (unsigned int zomIndex = 0; zomIndex < zomPtrs.size(); ++zomIndex) {
        FloatRect* zomBoundPtr = zomPtrs.at(zomIndex)->boundPtr;

        // If the zombie is dead, continue to the next zombie
        if (zomPtrs.at(zomIndex)->getLife() <= 0) {
            continue;
        }


        // Zombie in range
        const Vector2i& bulletBlastPos = splCanPtr->getBulletBlastPos();
        float zomCenterX = zomBoundPtr->left + zomBoundPtr->width / 2;
        float zomCenterY = zomBoundPtr->top + zomBoundPtr->height / 2;

        // Detects if the zombie is caught in blast
        if (isInRange(bulletBlastPos.x, bulletBlastPos.y, zomCenterX, zomCenterY, splCanPtr->blastRadius) ) {
            Zombie* zomPtr = zomPtrs.at(zomIndex);

            // Create a container for the attack damage
            Vector2i* atkDmgPtr = new Vector2i(splCanPtr->attackDamage, 0);
            MessageDispatcher::sendMessage(splCanPtr->getId(), zomPtr->getId(), 0, MessageType::HIT_ZOMBIE, atkDmgPtr);
        }


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
        // Delete when the goal is reached
        if (zomPtrs.at(index)->getLife() <= 0) {
            // Add to the zombie to be deleted
            modelGcTimerPtrs.push_back(new ModelGCTimer(zomPtrs.at(index)->getId(), timeDeletion));

            // Removed it from the zombies' list
            zomPtrs.erase(zomPtrs.begin() + index);
            break;
        }

        // When the zombie reached its goal destination
        if (zomPtrs.at(index)->goalIsReached()) {
            // Reduce the life of the player
            Settings::life -= 1;

            // Add to the zombie to be deleted
            modelGcTimerPtrs.push_back(new ModelGCTimer(zomPtrs.at(index)->getId(), timeDeletion));

            // Removed it from the zombies' list
            zomPtrs.erase(zomPtrs.begin() + index);
        }
    }
}

void GameScreenUpdate::updateBulletExplosions(const float& delta) {
    for (unsigned int index = 0; index < aniExpTimerPtrs.size(); ++index) {
        AnimationExplosionTimer* timerPtr = aniExpTimerPtrs.at(index);

        timerPtr->stateTime -= delta;
        // Delete the timer
        if (timerPtr->stateTime <= 0) {
            aniExpTimerPtrs.erase(aniExpTimerPtrs.begin() + index);
            delete timerPtr;
            --index;
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
    int fullLife = zomSpawnManagerPtr->getStageNumber() * 100;
    Zombie* newZom;
    float speed = 16;
    float rotation = 0;
    float width = 32;
    float height = 32;
    switch (spawnAreaNumber % 10) {
    case 0: newZom = new Zombie(new FloatRect(32 * 6, 0, width, height), fullLife, rotation, speed);
            newZom->setPath(path6_0);
        break;
    case 1: newZom = new Zombie(new FloatRect(32 * 14, 0, width, height), fullLife, rotation, speed);
            newZom->setPath(path14_0);
        break;
    case 2: newZom = new Zombie(new FloatRect(32 * 21, 0, width, height), fullLife, rotation, speed);
            newZom->setPath(path21_0);
        break;
    case 3: newZom = new Zombie(new FloatRect(32 * 29, 0, width, height), fullLife, rotation, speed);
            newZom->setPath(path29_0);
        break;
    case 4: newZom = new Zombie(new FloatRect(32 * 36, 0, width, height), fullLife, rotation, speed);
            newZom->setPath(path36_0);
        break;
    case 5: newZom = new Zombie(new FloatRect(32 * 44, 0, width, height), fullLife, rotation, speed);
            newZom->setPath(path44_0);
        break;
    case 6: newZom = new Zombie(new FloatRect(32 * 49, 32 * 8, width, height), fullLife, rotation, speed);
            newZom->setPath(path49_8);
        break;
    case 7: newZom = new Zombie(new FloatRect(32 * 0, 32 * 8, width, height), fullLife, rotation, speed);
            newZom->setPath(path0_8);
        break;
    case 8: newZom = new Zombie(new FloatRect(32 * 0, 32 * 23, width, height), fullLife, rotation, speed);
            newZom->setPath(path0_23);
        break;
    case 9: newZom = new Zombie(new FloatRect(32 * 49, 32 * 23, width, height), fullLife, rotation, speed);
            newZom->setPath(path49_23);
        break;
    default:
        break;
    }
    // Set the goal node, to be changed if needed
    newZom->goalNodePtr = path0_23.front();
    zomPtrs.push_back(newZom);
}

void GameScreenUpdate::restartGame() {
    gameOver = false;
    Settings::reset();
    zomSpawnManagerPtr->reset();

    for (unsigned int index = 0; index < zomPtrs.size(); ++index) {
        delete zomPtrs.at(index);
    }
    zomPtrs.clear();

    // Delete the timer
    for (unsigned int index = 0; index < modelGcTimerPtrs.size(); ++index) {
        delete modelGcTimerPtrs.at(index);
    }
    modelGcTimerPtrs.clear();
}


//--------------------- Setters --------------------------
void GameScreenUpdate::createCannon(const string& canName, const int& tileX, const int& tileY) {
    int attackDamage = 10;
    int range = 96;
    float attackDelay = 1.0f;
    float rotation = 0;
    float rotationSpeed = 100.0f;

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
const bool& GameScreenUpdate::isGameOver() {
    return gameOver;
}

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

    // Delete the timer
    for (unsigned int index = 0; index < modelGcTimerPtrs.size(); ++index) {
        delete modelGcTimerPtrs.at(index);
    }
}
