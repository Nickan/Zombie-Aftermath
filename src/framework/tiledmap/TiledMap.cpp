#include "TiledMap.h"


TiledMap::TiledMap(const Texture& texture, const float tileMap[], const unsigned int totalFrames,
            const unsigned int& tileWidth, const unsigned int& tileHeight,
            const unsigned int& rows, const unsigned int& columns, const unsigned int& scrWidth, const unsigned int& scrHeight)
{
    this->texture = texture;
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    this->rows = rows;
    this->columns = columns;
    this->screenWidth = scrWidth;
    this->screenHeight = scrHeight;

    initializeTileMap(tileMap);
    initializeCells();
    Image image;
    image = texture.copyToImage();


    for (unsigned int frameNum = 0; frameNum < totalFrames; ++frameNum) {
        unsigned int colNum = frameNum / columns;
        unsigned int rowNum = frameNum % columns;

        Texture tempTexture;
        tempTexture.loadFromImage(image, IntRect(rowNum * tileWidth, colNum * tileHeight, tileWidth, tileHeight));
        spritePtrList.push_back(new GameSprite(tempTexture, 0, 0));
    }
}

void TiledMap::initializeTileMap(const float tileMap[]) {
    // Assign the argument 1D array to 2D vector
    unsigned int totalTiles = columns * rows;
    unsigned int previousColumn = -1;

    for(unsigned int tileNum = 0; tileNum < totalTiles; ++tileNum) {
        unsigned int colNum = tileNum / columns;
        unsigned int rowNum = tileNum % columns;

        // Detects if it is in new column
        if (colNum != previousColumn) {
            previousColumn = colNum;
            vector<float> newColumn;
            tileInfo.push_back(newColumn);
        }

        tileInfo.at(colNum).push_back(tileMap[tileNum]);
    }
}

void TiledMap::initializeCells() {
    for (unsigned int i = 0; i < tileInfo.size(); ++i) {
        vector<Cell> cellRow;

        for (unsigned int j = 0; j < tileInfo.at(i).size(); ++j) {
            float tileId = tileInfo.at(i).at(j);

            cellRow.push_back(Cell(j * tileWidth, i * tileHeight, tileWidth, tileHeight, getRotationType(tileId)));
        }
        cells.push_back(cellRow);
    }
}

void TiledMap::draw(RenderWindow& win) {
    for (unsigned int i = 0; i < tileInfo.size(); ++i) {
        for (unsigned int j = 0; j < tileInfo.at(i).size(); ++j) {
            tileType = tileInfo.at(i).at(j);
            Cell& cell = cells.at(i).at(j);

            // Don't draw if the tile is null and out of screen;
            if ( (cell.left > (int) -tileWidth && cell.left < screenWidth + tileWidth) &&
                    (cell.top > (int) -tileHeight && cell.top < screenHeight + tileHeight) ) {
                if (tileType != -1) {
                    GameSprite* sprPtr = spritePtrList.at((unsigned int) tileType);
                    sprPtr->draw(win, cell.left, cell.top, cell.rotation);
                }
            }

        }
    }

}

void TiledMap::draw(RenderWindow& win, const float& x, const float& y) {
/*
    setPosition(x, y);
    for (unsigned int i = 0; i < tileSprite.size(); ++i) {
        for (unsigned int j = 0; j < tileSprite.at(i).size(); ++j) {
            tileType = tileInfo.at(i).at(j);
            position = tileSprite.at(i).at(j)->getPosition();

            // Don't draw if the tile is null and out of screen;
            if ( (position.x > -tileWidth && position.x < screenWidth + tileWidth) &&
                    (position.y > -tileHeight && position.y < screenHeight + tileHeight) ) {
                if (tileType != -1) {
                    tileSprite.at(i).at(j)->draw(win);
                }
            }
        }
    }
    */
}

void TiledMap::setPosition(const float& posX, const float& posY) {
    for (unsigned int i = 0; i < tileInfo.size(); ++i) {
        for (unsigned int j = 0; j < tileInfo.at(i).size(); ++j) {
//            tileSprite.at(i).at(j)->setPosition( (j * tileWidth) + posX, (i * tileHeight) + posY);
        }
    }
}

void TiledMap::setScreenSize(const Vector2i& s) {
    screenWidth = s.x;
    screenHeight = s.y;
}

void TiledMap::setScreenSize(const int& width, const int& height) {
    screenWidth = width;
    screenHeight = height;
}

float TiledMap::getRotationType(const float& tileID) {
    /* Extracting the decimal value to get the rotation type */
    int intTileID = tileID;
    float rotationExtractor = intTileID;
    float rotationType = tileID - rotationExtractor;          /* Returns the rotation indicator */

    if (rotationType > 0.09f && rotationType < 0.11f) {
        return 90;
    } else if (rotationType > 0.19f && rotationType < 0.21f) {
        return 180;
    } else if (rotationType > 0.29f && rotationType < 0.31f) {
        return 270;
    }
    return 0;
}

TiledMap::~TiledMap() {

}
