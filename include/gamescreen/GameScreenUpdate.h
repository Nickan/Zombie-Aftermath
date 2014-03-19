#ifndef GAMESCREENUPDATE_H
#define GAMESCREENUPDATE_H

#include <SFML/System/Vector2.hpp>

#include "AnimationExplosionTimer.h"
#include "AStarPathfinder.h"
#include "Cannon.h"
#include "IceCannon.h"
#include "SplashCannon.h"
#include "Zombie.h"
#include "MessageDispatcher.h"
#include "ModelGCTimer.h"
#include "ZombieSpawnManager.h"
#include "Settings.h"

#include <vector>

// For debugging
#include <iostream>
using namespace std;
using namespace sf;

class GameScreenRenderer;

class GameScreenUpdate {
    public:
        GameScreenUpdate();
        void update(const float& delta);

        // Set the tile map info for the path finding of the target coordinates of zombie
        void setTileMapInfo(vector<vector<float> >* tileMapInfoPtrs);

        void initializeMapInfo(const vector<vector<float> >& tileMapInfo);

        void createCannon(const string& canName, const int& x, const int& y);

        void restartGame();

        const bool& isGameOver();

        const vector<Zombie*>& getZombiePtrs();
        const vector<Cannon*>& getNorCanPtrs();
        const vector<SplashCannon*>& getSplCanPtrs();
        const vector<IceCannon*>& getIceCanPtrs();

        Vector2f mapPos;

        vector<vector<float> > tileStatus;

        ZombieSpawnManager* zomSpawnManagerPtr;

        vector<AnimationExplosionTimer*> aniExpTimerPtrs;

        virtual ~GameScreenUpdate();
    protected:
    private:
        void initializeZombieVariables();

        void updateZombies(const float& delta);

        void updateNormalCannon(const float& delta);
        void updateIceCannon(const float& delta);
        void updateSplashCannon(const float& delta);

        void handleIceBulletBlast(IceCannon* iceCanPtr);
        void handleSplashBulletBlast(SplashCannon* splCanPtr);

        void updateBulletExplosions(const float& delta);

        // Updates the deletion timer of registered to be deleted entity
        void updateModelGcTimer(const float& delta);
        void zombieDeletionManager();

        // Spawns zombie based on the area number
        void spawnZombie(const int& spawnAreaNumber);


        const bool zombieInRange(const FloatRect* canRect, const FloatRect* zomRect, const float& range);
        const bool isInRange(const float& x1, const float& y1, const float& x2, const float& y2, const float& range);

        AStarPathfinder* pathFinderPtr;

        vector<Zombie*> zomPtrs;
        vector<Cannon*> norCanPtrs;
        vector<SplashCannon*> splashCanPtrs;
        vector<IceCannon*> iceCanPtrs;

        vector<ModelGCTimer* > modelGcTimerPtrs;

        Vector2i* zomTarDistPtr;

        vector<Node*> path6_0;
        vector<Node*> path14_0;
        vector<Node*> path21_0;
		vector<Node*> path29_0;
		vector<Node*> path36_0;
		vector<Node*> path44_0;
		vector<Node*> path49_8;
		vector<Node*> path0_8;
		vector<Node*> path0_23;
		vector<Node*> path49_23;

        bool gameOver;
};

#endif // GAMESCREENUPDATE_H
