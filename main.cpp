#include <SFML/Graphics.hpp>

#include "ZombieAftermath.h"

#include "screen/GameScreen.h"
#include "framework/Timer.h"

using namespace sf;

int main()
{
    ZombieAftermath* gamePtr = new ZombieAftermath();
    gamePtr->setScreen(new GameScreen(gamePtr));
    Timer* timerPtr = new Timer();

    RenderWindow window(VideoMode(200, 200), "SFML works!");
    CircleShape shape(100.f);
    shape.setFillColor(Color::Green);

    while (window.isOpen())
    {
        float delta = timerPtr->getDeltaTime();
        gamePtr->update(delta);
        gamePtr->render(window, delta);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    delete gamePtr;
    delete timerPtr;
    return 0;
}
