#ifndef MINIMAP_H
#define MINIMAP_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "Cannon.h"
#include "GameSprite.h"
#include "ZombieAftermath.h"
#include "IceCannon.h"
#include "SplashCannon.h"
#include "Zombie.h"

//---------------------------------------------------------------------
//
// Minimap for HUD
//---------------------------------------------------------------------

using namespace sf;

class MiniMap {
    public:
        MiniMap();
        virtual ~MiniMap();

        void draw(RenderWindow& win, const vector<Zombie*> zomPtrs,
            const vector<Cannon*> norCanPtrs, const vector<SplashCannon*> splCanPtrs, const vector<IceCannon*> iceCanPtrs);

        void setImage(const Image& image);

        // Set the mini map's view rect based on the current view of the map
        void setViewRectPos(const float& x, const float& y);

        Vector2i pos;
    protected:
    private:
        GameSprite* bgSpritePtr;

        // Zombie indicator on the mini map
        CircleShape zomTriangle;

        // The current view of the map
        RectangleShape viewRect;

        Color zomColor;
        Color zomPathColor;
        Color bgColor;

        // Scale of the miniMap
        float mapScaleX;
        float mapScaleY;
};

#endif // MINIMAP_H
