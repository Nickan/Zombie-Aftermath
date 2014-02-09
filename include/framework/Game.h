#ifndef GAME_H
#define GAME_H
#include "SFML/Graphics.hpp"
#include "Screen.h"
#include "framework/Timer.h"

using namespace sf;

///
//#include <iostream>
//using namespace std;

class Game {
    public:
        Game(const float width, const float height);

        void setScreen(Screen* scr);
        void startLooping();

        void setScreenSize(const Vector2i& scrSize);
        const Vector2i& getScreenSize();

        float width;
        float height;
        virtual ~Game();
    protected:

        // Variables to set the mouse update speed
        float updateTime;
        float cumulativeTime;

        Screen* scrPtr;
        Vector2i screenSize;

        // Newly created variables
        Timer* timerPtr;
    private:
};

#endif // GAME_H
