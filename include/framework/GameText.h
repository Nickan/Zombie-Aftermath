#ifndef GAMETEXT_H
#define GAMETEXT_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include <iostream>

using namespace sf;
using namespace std;

//----------------------------------------------------
//
// A simple wrapper for drawing text on the screen
//----------------------------------------------------

class GameText {
    public:
        GameText(const string& fontPath);
        virtual ~GameText();

        void draw(RenderWindow& win, const string& str, const float& x, const float& y, const Color& color);

        void setCharSize(const float& charSize);
    protected:
    private:
        Font font;
        Text text;
};

#endif // GAMETEXT_H
