#ifndef GAMESCREENRENDERER_H
#define GAMESCREENRENDERER_H

#include <SFML/Graphics.hpp>

#include "TileInfo.h"
#include "TiledMap.h"
#include "TextureAtlas.h"

#include <vector>

#include "GameSprite.h"

using namespace sf;

// For debugging
#include <iostream>
using namespace std;

class GameScreenUpdate;

class GameScreenRenderer {
    public:
        GameScreenRenderer(GameScreenUpdate* updatePtr);
        void render(RenderWindow& win, const float& delta);

        TiledMap* tiledMapPtr;
        virtual ~GameScreenRenderer();
    protected:
    private:
        GameScreenUpdate* updatePtr;

        GameSprite* tempSpritePtr;
};

#endif // GAMESCREENRENDERER_H
