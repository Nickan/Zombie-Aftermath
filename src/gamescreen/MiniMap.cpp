#include "MiniMap.h"

MiniMap::MiniMap() {
    pos.x = 0;
    pos.y = 32 * 14;

    zomColor = Color::Yellow;

    // Setting up the cursor for zombie, a triangle
    zomTriangle.setRadius(5);
    zomTriangle.setPointCount(3);
    zomTriangle.setOrigin(zomTriangle.getRadius(), zomTriangle.getRadius());
    zomTriangle.setFillColor(zomColor);
}


void MiniMap::draw(RenderWindow& win, const vector<Zombie*> zomPtrs, const vector<Cannon*> norCanPtrs,
    const vector<SplashCannon*> splCanPtrs, const vector<IceCannon*> iceCanPtrs) {

    bgSpritePtr->draw(win);

    for (unsigned int index = 0; index < zomPtrs.size(); ++index) {
        Zombie* zomPtr = zomPtrs.at(index);

        // Added one pixel in x-axis for visual correction
        float posX = pos.x + ( (zomPtr->boundPtr->left + (zomPtr->boundPtr->width / 2) ) * mapScaleX) + 1;
        float posY = pos.y + ( (zomPtr->boundPtr->top + (zomPtr->boundPtr->height / 2) ) * mapScaleY);
        zomTriangle.setPosition(posX, posY);

        // Visual correction the direct the triagle to where the zombie is viewing
        zomTriangle.setRotation(zomPtr->rotation - 90);
        win.draw(zomTriangle);
    }

    // View rect
    win.draw(viewRect);
}

void MiniMap::setImage(const Image& image) {
    Texture bgTexture;
    bgTexture.loadFromImage(image);
    bgSpritePtr = new GameSprite(bgTexture, pos.x, pos.y);

    const IntRect& bgRec = bgSpritePtr->getBounds();

    mapScaleX = 0.15f;
    mapScaleY = 0.125f;

    bgSpritePtr->setScale(mapScaleX, mapScaleY);
    float miniMapWidth = (bgRec.width * mapScaleX);
    float miniMapHeight = (bgRec.height * mapScaleY);
    bgSpritePtr->setPosition( ( (miniMapWidth / 2) - (bgRec.width / 2) ) + pos.x,
        ( (miniMapHeight / 2) - (bgRec.height / 2) ) + pos.y);

    bgColor = Color::Green;
//    bgColor.b = 255;
//    bgColor.r = 150;
//    bgColor.a = 200;
    bgSpritePtr->setColor(bgColor);

    // View rect
    // The view rect width is half the mini map, while the height is just one-third
    viewRect.setSize( Vector2f(miniMapWidth / 2, miniMapHeight / 3) );
    viewRect.setFillColor(Color::Transparent);
    viewRect.setOutlineColor(Color::White);
    viewRect.setOutlineThickness(1);
}


void MiniMap::setViewRectPos(const float& x, const float& y) {
    // Needs to put allowance on the height, as the top panel covers the first column tiles
    float topTileAllowance = (32 * mapScaleY);

    // Reverse of the coordinate
    float posY = pos.y - (y * mapScaleY);
    float posX = pos.x - (x * mapScaleX);
    viewRect.setPosition(posX, posY + topTileAllowance);
}

MiniMap::~MiniMap() {
    delete bgSpritePtr;
}
