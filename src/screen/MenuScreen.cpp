#include "MenuScreen.h"

MenuScreen::MenuScreen(ZombieAftermath* gamePtr)
{
    Image image;
    image.loadFromFile("assets/allmenuimages.png");
    Texture texture;
    texture.setSmooth(true);

    texture.loadFromImage(image, IntRect(0, 0, 800, 80));
    aniCursorPtr = new Animation(texture, 80, 80, 10, 10, 0.5f, Animation::LOOP);
    aniCursorPtr->setScale(1.1f, 0.65f);
    aniCursorPtr->setPosition(0, 0);

    tempStateTime = 0;

}

void MenuScreen::render(RenderWindow& win, const float& delta) {
    tempStateTime += delta;
//    cout << "Rendering" << endl;
    aniCursorPtr->draw(win, tempStateTime);
}

MenuScreen::~MenuScreen()
{
    delete aniCursorPtr;
}
