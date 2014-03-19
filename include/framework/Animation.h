#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

using namespace sf;

//---------------------------------------------------------------------------------
//  Plays an animation from texture sprite sheet, set the origin to the center
//  (as I don't see a reason as of now that the origin shouldn't be set this way)
//---------------------------------------------------------------------------------


// For debugging
#include <iostream>
using namespace std;

class Animation {
    public:
//        Animation();
        Animation(Texture& t, const int width, const int height, const int totalColumns, const int totalFrames,
                    const float duration, const int playMode);
        void init();

        void draw(RenderWindow&, float& stateTime);
        void draw(RenderWindow&, const float&, const float&, const float& rotation, const float& stateTime);

        void setPosition(const float&, const float&);
        void setRotation(const float&);
        void setScale(const float&, const float&);

        void setStartingFrame(const int&);
        void setEndingFrame(const int&);

        const int& getWidth();
        const int& getHeight();

        const Vector2f& getPosition();

        ///< Testing
        void setNextRow(const bool&);

        static const int NORMAL;
        static const int LOOP;
        virtual ~Animation();
    protected:
        void updateSprite(const float& stateTime);
    private:
        int width;
        int height;
        int totalColumns;
        int totalFrames;
        int currentFrame;
        int frameX;
        int frameY;

        float duration;

        Vector2f position;

        Texture texture;
        Sprite sprite;
        IntRect drawRect;

        int playMode;
};

#endif // ANIMATION_H
