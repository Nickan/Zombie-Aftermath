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
#include "PurchasePanel.h"

using namespace sf;

// For debugging
#include <iostream>
using namespace std;

class GameScreenUpdate;

class GameScreenRenderer {
    public:
        GameScreenRenderer(GameScreenUpdate* updatePtr);
        void render(RenderWindow& win, const float& delta);

        const vector<vector<float> >& getTileMapInfo();

        PurchasePanel* purchasePanPtr;

        virtual ~GameScreenRenderer();
    protected:
    private:

        void drawNormalCannons(RenderWindow& win, const vector<Cannon*>& canPtrs);
        void drawIceCannons(RenderWindow& win, const vector<IceCannon*>& canPtrs);
        void drawSplashCannons(RenderWindow& win, const vector<SplashCannon*>& canPtrs);

        Animation* aniZomPtr;
        GameScreenUpdate* updatePtr;

        TiledMap* tiledMapPtr;

        RectangleShape lifeIndicator;

        TextureAtlas* textureAtlasPtr;
};

#endif // GAMESCREENRENDERER_H
