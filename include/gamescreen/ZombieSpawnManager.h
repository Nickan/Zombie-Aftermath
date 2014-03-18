#ifndef ZOMBIESPAWNMANAGER_H
#define ZOMBIESPAWNMANAGER_H


class ZombieSpawnManager {
    public:
        ZombieSpawnManager();
        virtual ~ZombieSpawnManager();

        const bool spawnZombie(const float& delta);

        // Reset to stage one
        void reset();

        // Increase the stage
        void stageUp();

        const int& getStageNumber();

        int totalSpawn;
    protected:
    private:
        int stage;
        int spawnLimit;
        float spawnTimer;
        float spawnInterval;
};

#endif // ZOMBIESPAWNMANAGER_H
