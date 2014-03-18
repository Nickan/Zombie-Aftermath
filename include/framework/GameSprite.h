#ifndef GAMESPRITE_H
#define GAMESPRITE_H

#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

using namespace sf;
using namespace std;

// Saves the texture being passed if instantiated as a pointer, as Sprite class doesn't save a copy of texture being passed to it,
// and automatically sets the pivot for rotation on the center, as up until now, I don't see any clear reason why I should not.
// But later I will change it if I need to.

class GameSprite {
    public:
        GameSprite();
        GameSprite(const string& filePath);
        GameSprite(Texture&, const int x, const int y);

        void loadFromFile(const string& filePath);
        void setTexture(Texture& texture);
        void draw(RenderWindow& win);
        void draw(RenderWindow&, const int& x, const int& y, const float& rotation);
        void setColor(const Color& color);
        void setPosition(const int& x, const int& y);
        void setScale(const float& scaleX, const float& scaleY);
        void setRotation(const float& rotation);

        const Vector2f& getPosition();
        const IntRect& getBounds();

        virtual ~GameSprite();
    protected:
    private:
        Texture texture;
        Sprite sprite;
        IntRect bounds;

        void initialize();
};

#endif // GAMESPRITE_H
