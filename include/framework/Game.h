#ifndef GAME_H
#define GAME_H
#include "SFML/Graphics.hpp"
#include "Screen.h"

using namespace sf;

///
//#include <iostream>
//using namespace std;

class Game {
    public:
        Game();
        void update(const float&);
        void render(RenderWindow&, const float&);
        void setScreen(Screen*);
        void close();

        void setScreenSize(const Vector2i&);
        const Vector2i& getScreenSize();

        virtual ~Game();
    protected:
        float updateTime;
        float cumulativeTime;

        Screen* screenPtr;
        Vector2i screenSize;
    private:
        bool closed;
};

#endif // GAME_H
