#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
//#include "Input.h"

using namespace sf;

class Screen {
    public:
        Screen();
        virtual void update(const float&) = 0;
        virtual void render(RenderWindow&, const float&) = 0;

        void updateInputEvent(RenderWindow&, Event&);
        void updateMouseMotion(RenderWindow&);
//        void setInput(Input*);
        virtual ~Screen();
    protected:
    private:
//        Input* inputPtr;
        Vector2i mousePos;
};

#endif // SCREEN_H
