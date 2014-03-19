#include "ZombieSpawnManager.h"

ZombieSpawnManager::ZombieSpawnManager() {
    reset();
}

void ZombieSpawnManager::update(const float& delta) {
    if (spawnCountDown < 0) {
        spawnTimer += delta;

        if (spawnTimer >= spawnInterval) {
            spawnTimer -= spawnInterval;

            if (currentSpawnedZombies < spawnLimit) {
                ++currentSpawnedZombies;
                ++totalSpawnedZombies;
                spawn = true;
            }
        }
    } else {
        spawnCountDown -= delta;
    }
}

const bool ZombieSpawnManager::spawnZombie() {
    if (spawn) {
        spawn = false;
        return true;
    }
    return false;
}

const bool ZombieSpawnManager::stoppedSpawning() {
    return (currentSpawnedZombies >= spawnLimit) ? true : false;
}

void ZombieSpawnManager::reset() {
    currentSpawnedZombies = 0;
    spawnCountDown = 5;
    spawnLimit = 5;
    stage = 1;
    totalSpawnedZombies = 0;

    spawnInterval = 1.0f;
    spawnTimer = 0.0f;

    spawn = false;
}

void ZombieSpawnManager::incrementStage() {
    ++stage;
    spawnCountDown = 5;
    spawnLimit = (spawnLimit * 1.5f);
    spawnTimer = 0;
    currentSpawnedZombies = 0;
}

const int& ZombieSpawnManager::getStageNumber() {
    return stage;
}

const int& ZombieSpawnManager::getTotalSpawn() {
    return totalSpawnedZombies;
}

const float& ZombieSpawnManager::getSpawnCountDown() {
    return spawnCountDown;
}

ZombieSpawnManager::~ZombieSpawnManager() {
    //dtor
}
