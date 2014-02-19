#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "ZombieAftermath.h"
#include "Screen.h"
#include "Animation.h"


// For debugging
#include <iostream>
using namespace std;

class MenuScreen : public Screen
{
    public:
        MenuScreen(ZombieAftermath* gamePtr);
        void render(RenderWindow& win, const float& delta);
        virtual ~MenuScreen();
    protected:
    private:
        ZombieAftermath* gamePtr;
        Animation* aniCursorPtr;


        float tempStateTime;
};

#endif // MENUSCREEN_H
