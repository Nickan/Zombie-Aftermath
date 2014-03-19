#ifndef ZOMBIESPAWNMANAGER_H
#define ZOMBIESPAWNMANAGER_H


#include <iostream>
using namespace std;

class ZombieSpawnManager {
    public:
        ZombieSpawnManager();
        virtual ~ZombieSpawnManager();

        void update(const float& delta);

        const bool spawnZombie();
        const bool stoppedSpawning();

        const float& getSpawnCountDown();

        // Reset to stage one
        void reset();

        // Increase the stage
        void incrementStage();

        const int& getStageNumber();
        const int& getTotalSpawn();
    protected:
    private:
        int currentSpawnedZombies;
        int stage;
        int spawnLimit;
        int totalSpawnedZombies;
        float spawnCountDown;
        float spawnTimer;
        float spawnInterval;

        bool spawn;
};

#endif // ZOMBIESPAWNMANAGER_H
