#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Screen.h"
#include "ZombieAftermath.h"

class GameScreen : public Screen
{
    public:
        GameScreen(ZombieAftermath*);
        void update(const float&);
        void render(RenderWindow& win, const float&);
        ~GameScreen();
    protected:
        ZombieAftermath* gamePtr;
    private:
};

#endif // GAMESCREEN_H
