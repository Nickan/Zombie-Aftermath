#include "ZombieAftermath.h"

#include "screen/GameScreen.h"

using namespace sf;

int main()
{
    ZombieAftermath* gamePtr = new ZombieAftermath(800, 600);
    gamePtr->setScreen(new GameScreen(gamePtr));

    // Starts the never ending looping unless it is closed
    gamePtr->startLooping();
    delete gamePtr;
    return 0;
}
