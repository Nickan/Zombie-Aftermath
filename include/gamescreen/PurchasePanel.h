#ifndef PURCHASEPANEL_H
#define PURCHASEPANEL_H

#include "TextureAtlas.h"
#include <SFML/Graphics/Rect.hpp>
#include <array>

//-------------------------------------------------------------------
//
//  Handles the drawing and the button id for input of purchase panel
//-------------------------------------------------------------------

class PurchasePanel {
    public:
        PurchasePanel(TextureAtlas* textureAtlasPtr);
        virtual ~PurchasePanel();

        void draw(RenderWindow& win, const int& x, const int& y);

        // Returns the id of the rect being touched
        const int getButtonId(const int& touchX, const int& touchY);

        string canName;
        int cursorX;
        int cursorY;
    protected:
    private:
        TextureAtlas* textureAtlasPtr;
        array<IntRect*, 3> buttonPtrs;

        // Just to prevent creating many copy (or it is just my assumption)
        IntRect cannonRect;
};

#endif // PURCHASEPANEL_H
