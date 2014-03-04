#ifndef TILEDMAP_H
#define TILEDMAP_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>


#include "GameSprite.h"
#include <vector>
#include "Cell.h"

using namespace sf;
using namespace std;

///
#include <iostream>

// Got back from Java, there is really no way to make a 2D array in C++ without setting the range value of the
// after the first dimension. So using a 1D array, as a map, it will create a 2D vector.
// Since there seems no way of initializing vector like in Java, and Array can't be passed as an argument in vector template,
// 1D array is my last resort to create a map to be passed here and ease the process of Tile mapping

// Initializing texture atlas from a texture and addressing tile by the passed width and height.

class TiledMap {
    public:
        TiledMap(const Texture& texture, const float tileMap[], const unsigned int totalFrames,
            const unsigned int& tileWidth, const unsigned int& tileHeight,
            const unsigned int& rows, const unsigned int& columns, const unsigned int& scrWidth, const unsigned int& scrHeight);

        void draw(RenderWindow&);
        void draw(RenderWindow&, const float&, const float&);

        void setPosition(const float&, const float&);
        void setScreenSize(const Vector2i&);
        void setScreenSize(const int&, const int&);

        vector<vector<float> > tileInfo;
        vector<vector<Cell> > cells;

        virtual ~TiledMap();
    protected:
    private:
        unsigned int columns;
        unsigned int rows;
        unsigned int tileWidth;
        unsigned int tileHeight;
        unsigned int verticalMapNumber;
        unsigned int currentMapNumber;
        unsigned int startingRowNumber;
        unsigned int tileType;
        unsigned int screenWidth;
        unsigned int screenHeight;
        Vector2f position;

        Texture texture;
        vector<GameSprite* > spritePtrList;

        void initializeTileMap(const float tileMap[]);

        float getRotationType(const float&);

        void initializeCells();
};

#endif // TILESPRITES_H
