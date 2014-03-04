#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "ZombieAftermath.h"
#include "Screen.h"
#include "Animation.h"
#include "GameSprite.h"
#include "Settings.h"
#include "MenuScreenInput.h"

// For debugging
#include <iostream>
using namespace std;

class MenuScreen : public Screen
{
    public:
        MenuScreen(ZombieAftermath* gamePtr);
        void render(RenderWindow& win, const float& delta);


        const int& getPlaySpriteX();
        const int& getPlaySpriteY();

        ZombieAftermath* getGamePtr();

        const IntRect& getPlayRect();
        const IntRect& getExitRect();
        const IntRect& getSoundButtonRect();

        void setCursorOnStart();
        void setCurosrOnExit();

        void setDrawCursor(const bool&);

        virtual ~MenuScreen();
    protected:
    private:
        int playSpriteX;
        int playSpriteY;
        bool drawCursor;

        IntRect playRect;
        IntRect exitRect;
        IntRect soundRect;

        ZombieAftermath* gamePtr;
        Animation* aniCursorPtr;

        GameSprite* playSpritePtr;
        GameSprite* exitSpritePtr;
        GameSprite* gameTitleSpritePtr;
        GameSprite* soundEnableSpritePtr;
        GameSprite* soundDisableSpritePtr;

        float tempStateTime;
};

#endif // MENUSCREEN_H
