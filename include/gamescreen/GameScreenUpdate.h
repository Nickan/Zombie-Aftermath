#ifndef GAMESCREENUPDATE_H
#define GAMESCREENUPDATE_H

#include "RotationManager.h"
#include <SFML/System/Vector2.hpp>

// For debugging
#include <iostream>
using namespace std;
using namespace sf;

class GameScreenUpdate
{
    public:
        GameScreenUpdate();
        void update(const float& delta);

        Vector2f mapPos;
        virtual ~GameScreenUpdate();
    protected:
    private:
};

#endif // GAMESCREENUPDATE_H
