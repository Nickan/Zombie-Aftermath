#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Screen.h"
#include "ZombieAftermath.h"
#include "GameScreenController.h"

// For debugging
#include <iostream>
using namespace std;

class GameScreen : public Screen
{
    public:
        GameScreen(ZombieAftermath* gamePtr);
        void render(RenderWindow& win, const float& delta);
        ~GameScreen();
    protected:
        ZombieAftermath* gamePtr;

        CircleShape circle;
    private:
};

#endif // GAMESCREEN_H
