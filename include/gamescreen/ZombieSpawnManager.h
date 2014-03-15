#ifndef ZOMBIESPAWNMANAGER_H
#define ZOMBIESPAWNMANAGER_H


class ZombieSpawnManager {
    public:
        ZombieSpawnManager();
        virtual ~ZombieSpawnManager();

        const bool spawnZombie(const float& delta);


        int totalSpawn;
        int spawnLimit;
        float spawnTimer;
        float spawnInterval;
    protected:
    private:
};

#endif // ZOMBIESPAWNMANAGER_H
