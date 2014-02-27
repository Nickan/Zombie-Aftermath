#include "ZombieAftermath.h"

#include "GameScreen.h"
#include "MenuScreen.h"

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
