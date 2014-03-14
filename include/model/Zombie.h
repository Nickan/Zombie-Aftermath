#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Entity.h"
#include "MessageDispatcher.h"
#include "Node.h"

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <vector>

using namespace sf;

//... For detection
#include <iostream>
using namespace std;


//------------------------------------------------------------------
//
// Zombie that knows how to track the node path that is given to it
//------------------------------------------------------------------

class Zombie : public Entity {
    public:
        Zombie(FloatRect* boundPtr, const float& rotation, const float& speed);

        void update(const float& delta);

        void setPath(const vector<Node*>& pathPtrs);
        const bool handleMessage(Message* msgPtr);

        const float& getLife();
        const float& getFullLife();

        float stateTime;
        virtual ~Zombie();
    protected:
    private:

        // Will be called when there the zombie is not moving and there is still a path in the path list
        void setMovement();

        unsigned int worldUnit;
        float speed;
        float rotationSpeed;
        float life;
        float fullLife;
        Vector2i velocity;
        Vector2f previousPos;
        vector<Node* > pathPtrs;
};

#endif // ZOMBIE_H
