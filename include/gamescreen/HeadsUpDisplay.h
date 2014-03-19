#ifndef HEADSUPDISPLAY_H
#define HEADSUPDISPLAY_H

#include <SFML/Graphics/RectangleShape.hpp>

#include "GameText.h"
#include "MiniMap.h"
#include "Settings.h"
#include "TextureAtlas.h"
#include "ToString.h"
#include "ZombieSpawnManager.h"

enum CannonType {
    NORMAL_CANNON, ICE_CANNON, SPLASH_CANNON, NONE,
};

class HeadsUpDisplay {
    public:
        HeadsUpDisplay(TextureAtlas* textureAtlasPtr);
        virtual ~HeadsUpDisplay();

        void draw(RenderWindow& win);
        void drawGameOver(RenderWindow& win);
        void drawMinimap(RenderWindow& win, const vector<Zombie*> zomPtrs,
            const vector<Cannon*> norCanPtrs, const vector<SplashCannon*> splCanPtrs, const vector<IceCannon*> iceCanPtrs);

        void drawZomSpawnManager(RenderWindow& win, ZombieSpawnManager* zomSpawnManagerPtr);

        void setCannonSpecs(const CannonType& cannonType);
        void setRestartButtonOpaque(const bool&);
        void setMenuButtonOpaque(const bool&);

        void setMiniMapBgImage(const Image& image);
        void setMiniMapViewRect(const float& x, const float& y);

        const bool isOverRestartButton(const int& x, const int& y);
        const bool isOverMenuButton(const int& x, const int& y);
    protected:
    private:
        TextureAtlas* textureAtlasPtr;
        GameText* gameTextPtr;

        RectangleShape bgRect;

        Color restartColor;
        Color menuColor;

        IntRect restartRect;
        IntRect menuRect;

        MiniMap* miniMapPtr;

        // For showing the specs of the cannon
        CannonType showCannonSpecs;
};

#endif // HEADSUPDISPLAY_H
