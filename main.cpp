#include "ZombieAftermath.h"

#include "screen/GameScreen.h"
#include "screen/MenuScreen.h"

using namespace sf;

int main()
{
    ZombieAftermath* gamePtr = new ZombieAftermath(800, 600, "Zombie Aftermath");
    gamePtr->setScreen(new MenuScreen(gamePtr));

    // Starts the never ending looping unless it is closed
    gamePtr->startLooping();
    delete gamePtr;
    return 0;
}
