#ifndef CANNONATTACKSTATE_H
#define CANNONATTACKSTATE_H

#include "State.h"
#include "Cannon.h"
#include "Zombie.h"

//... For detection
#include <iostream>
using namespace std;

class Cannon;

class CannonAttackState : public State<Cannon> {
    public:
        static CannonAttackState* getInstance();

        void start(Cannon* canPtr);
        void update(Cannon* canPtr, const float& delta);
        void exit(Cannon* canPtr);

    protected:
    private:
        CannonAttackState();
        virtual ~CannonAttackState();

        static CannonAttackState instance;
};

#endif // CANNONATTACKSTATE_H
