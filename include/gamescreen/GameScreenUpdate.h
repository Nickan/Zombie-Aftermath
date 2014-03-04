#ifndef GAMESCREENUPDATE_H
#define GAMESCREENUPDATE_H

#include "RotationManager.h"

// For debugging
#include <iostream>
using namespace std;

class GameScreenUpdate
{
    public:
        GameScreenUpdate();
        void update(const float& delta);

        virtual ~GameScreenUpdate();
    protected:
    private:
};

#endif // GAMESCREENUPDATE_H
