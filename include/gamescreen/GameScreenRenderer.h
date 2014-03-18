#ifndef GAMESCREENRENDERER_H
#define GAMESCREENRENDERER_H

#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "HeadsUpDisplay.h"
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
        virtual ~GameScreenRenderer();
        void render(RenderWindow& win, const float& delta);

        const vector<vector<float> >& getTileMapInfo();

        PurchasePanel* purchasePanPtr;
        HeadsUpDisplay* hudPtr;
    protected:
    private:

        void drawNormalCannons(RenderWindow& win, const vector<Cannon*>& canPtrs);
        void drawIceCannons(RenderWindow& win, const vector<IceCannon*>& canPtrs);
        void drawSplashCannons(RenderWindow& win, const vector<SplashCannon*>& canPtrs);
        void drawZombies(RenderWindow& win);

        // Captures the whole background for mini map
        void captureBackground(RenderWindow& win);

        Animation* aniZomPtr;
        GameScreenUpdate* updatePtr;

        TiledMap* tiledMapPtr;

        RectangleShape lifeIndicator;
        Vector2f lifeSize;

        TextureAtlas* textureAtlasPtr;

        //...
        bool hasBgImage;
        Image fullBgImage;
};

#endif // GAMESCREENRENDERER_H
