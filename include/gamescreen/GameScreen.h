#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Screen.h"
#include "ZombieAftermath.h"
#include "GameScreenController.h"
#include "GameScreenUpdate.h"
#include "GameScreenRenderer.h"

// For debugging
#include <iostream>
using namespace std;

class GameScreen : public Screen {
    public:
        GameScreen(ZombieAftermath* gamePtr);
        void render(RenderWindow& win, const float& delta);
        ~GameScreen();
    protected:
        ZombieAftermath* gamePtr;

        GameScreenUpdate* updatePtr;
        GameScreenRenderer* rendererPtr;
    private:
};

#endif // GAMESCREEN_H
