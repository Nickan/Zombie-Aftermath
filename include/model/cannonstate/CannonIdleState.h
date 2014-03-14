#ifndef CANNONIDLESTATE_H
#define CANNONIDLESTATE_H

#include "State.h"
#include "Cannon.h"

//...
#include <iostream>
using namespace std;

class Cannon;

//-----------------------------------------------
//
// Defines the behavior of the cannon when not attack and searching for enemy
//-----------------------------------------------
class CannonIdleState : public State<Cannon> {
    public:
        static CannonIdleState* getInstance();

        void start(Cannon* cannonPtr);
        void update(Cannon* cannonPtr, const float& delta);
        void exit(Cannon* cannonPtr);

    protected:
    private:
        CannonIdleState();
        virtual ~CannonIdleState();

        static CannonIdleState instance;
};

#endif // CANNONIDLESTATE_H
