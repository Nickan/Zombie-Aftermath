#include "ZombieSpawnManager.h"

ZombieSpawnManager::ZombieSpawnManager() {
    reset();
}

const bool ZombieSpawnManager::spawnZombie(const float& delta) {
    spawnTimer += delta;
    if (spawnTimer >= spawnInterval) {
        spawnTimer -= spawnInterval;

        if (totalSpawn < spawnLimit) {
            ++totalSpawn;
            return true;
        }
    }
    return false;
}

void ZombieSpawnManager::reset() {
    totalSpawn = -1;
    spawnLimit = 100;
    spawnInterval = 1.0f;
    spawnTimer = 0.0f;
    stage = 1;
}

void ZombieSpawnManager::stageUp() {
    ++stage;
    spawnLimit * stage;
}

const int& ZombieSpawnManager::getStageNumber() {
    return stage;
}

ZombieSpawnManager::~ZombieSpawnManager() {
    //dtor
}
