#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Input.h"

using namespace sf;

class Screen {
    public:
        Screen();
        virtual void update(const float& delta) = 0;
        virtual void render(RenderWindow&, const float& delta) = 0;

        // Will be called when there is an event
        void updateInputEvent(RenderWindow&, Event&);

        // Always being called at fixed frequency, I don't know why I put this function before, I might change this later
        void updateMouseMotion(RenderWindow&);

        void setInput(Input*);
        virtual ~Screen();
    protected:
    private:
        Input* inputPtr;
        Vector2i mousePos;
};

#endif // SCREEN_H
