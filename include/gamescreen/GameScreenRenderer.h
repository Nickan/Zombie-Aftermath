#ifndef GAMESCREENRENDERER_H
#define GAMESCREENRENDERER_H

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "TileInfo.h"
#include "TiledMap.h"
#include "TextureAtlas.h"

#include <vector>

#include "GameSprite.h"
#include "GameScreenUpdate.h"

using namespace sf;

// For debugging
#include <iostream>
using namespace std;

class GameScreenUpdate;

class GameScreenRenderer {
    public:
        GameScreenRenderer(GameScreenUpdate* updatePtr);
        void render(RenderWindow& win, const float& delta);

        virtual ~GameScreenRenderer();
    protected:
    private:

        Animation* aniZomPtr;
        GameScreenUpdate* updatePtr;
        GameSprite* norCanSpritePtr;
        GameSprite* norCanBulSpritePtr;
        TiledMap* tiledMapPtr;

        RectangleShape lifeIndicator;
};

#endif // GAMESCREENRENDERER_H
