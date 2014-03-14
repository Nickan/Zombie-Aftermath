#ifndef GAMESCREENUPDATE_H
#define GAMESCREENUPDATE_H

#include <SFML/System/Vector2.hpp>

#include "AStarPathfinder.h"
#include "Cannon.h"
#include "Zombie.h"
#include "MessageDispatcher.h"
#include "ModelGCTimer.h"

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

        const vector<Zombie*>& getZombiePtrs();
        const vector<Cannon*>& getNorCanPtrs();

        Vector2f mapPos;

        vector<vector<float> >* tileInfoPtr;
        virtual ~GameScreenUpdate();
    protected:
    private:
        void initializeZombieVariables();


        void updateNormalCannon(const float& delta);

        // Updates the deletion timer of registered to be deleted entity
        void updateModelGcTimer(const float& delta);
        void zombieDeletionManager();

        const bool zombieInRange(const FloatRect* canRect, const FloatRect* zomRect, const float& range);
        const bool isInRange(const float& x1, const float& y1, const float& x2, const float& y2, const float& range);


        AStarPathfinder* pathFinderPtr;

        vector<Zombie*> zomPtrs;
        vector<Cannon*> norCanPtrs;

        vector<ModelGCTimer* > modelGcTimerPtrs;

        Vector2i* zomTarDistPtr;
};

#endif // GAMESCREENUPDATE_H
