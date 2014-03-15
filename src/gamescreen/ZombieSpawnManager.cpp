#include "ZombieSpawnManager.h"

ZombieSpawnManager::ZombieSpawnManager() {
    totalSpawn = -1;
    spawnLimit = 100;
    spawnInterval = 1.0f;
    spawnTimer = 0.0f;
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

ZombieSpawnManager::~ZombieSpawnManager() {
    //dtor
}
