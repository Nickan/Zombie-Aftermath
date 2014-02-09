#include "GameScreen.h"

GameScreen::GameScreen(ZombieAftermath* gamePtr)
{
    this->gamePtr = gamePtr;
}

void GameScreen::update(const float&)
{
}

void GameScreen::render(RenderWindow& win, const float&)
{
}

GameScreen::~GameScreen()
{
    //dtor
}
