#include "PurchasePanel.h"

PurchasePanel::PurchasePanel(TextureAtlas* textureAtlasPtr)
: textureAtlasPtr(textureAtlasPtr) {
    for (unsigned int index = 0; index < 3; ++index) {
        buttonPtrs.at(index) = new IntRect(0, 0, 32, 32);
    }

    canName = "";

    panelRect.width = 128;
    panelRect.height = 96;
}

void PurchasePanel::draw(RenderWindow& win, const int& x, const int& y) {
    panelRect.left = x;
    panelRect.top = y;

    // Pane background
    textureAtlasPtr->getSprite("panelcorner")->draw(win, x, y, 0.0);
    textureAtlasPtr->getSprite("panelside")->draw(win, x + 32, y, 0.0);
    textureAtlasPtr->getSprite("panelside")->draw(win, x + 64, y, 0.0);
    textureAtlasPtr->getSprite("panelcorner")->draw(win, x + 96, y, 90);

    textureAtlasPtr->getSprite("panelside")->draw(win, x + 0, y + 32, 270);
    textureAtlasPtr->getSprite("panelclear")->draw(win, x + 32, y + 32, 0);
    textureAtlasPtr->getSprite("panelclear")->draw(win, x + 64, y + 32, 0);
    textureAtlasPtr->getSprite("panelside")->draw(win, x + 96, y + 32, 90);

    textureAtlasPtr->getSprite("panelcorner")->draw(win, x + 0, y + 64, 270);
    textureAtlasPtr->getSprite("panelside")->draw(win, x + 32, y + 64, 180);
    textureAtlasPtr->getSprite("panelside")->draw(win, x + 64, y + 64, 180);
    textureAtlasPtr->getSprite("panelcorner")->draw(win, x + 96, y + 64, 180);

    // Button positions
    buttonPtrs.at(0)->left = x + 8;
    buttonPtrs.at(0)->top = y + 4;
    buttonPtrs.at(1)->left = x + 32 + 16;
    buttonPtrs.at(1)->top = y + 4;
    buttonPtrs.at(2)->left = x + 64 + 24;
    buttonPtrs.at(2)->top = y + 4;

    // Box button background
    GameSprite* boxSpritePtr = textureAtlasPtr->getSprite("square");
    boxSpritePtr->draw(win, buttonPtrs.at(0)->left, buttonPtrs.at(0)->top, 0);
    boxSpritePtr->draw(win, buttonPtrs.at(1)->left, buttonPtrs.at(1)->top, 0);
    boxSpritePtr->draw(win, buttonPtrs.at(2)->left, buttonPtrs.at(2)->top, 0);


    {   // Icon cannon to be purchased
    // Normal cannon
    GameSprite* canSpritePtr = textureAtlasPtr->getSprite("normalcannon");
    canSpritePtr->setScale(1.5f, 1.5f);
    cannonRect = canSpritePtr->getBounds();
    canSpritePtr->draw(win, (buttonPtrs.at(0)->left + 16) - cannonRect.width / 2,
                        (buttonPtrs.at(0)->top + 16) - cannonRect.height / 2, 0);

    // Splash cannon
    canSpritePtr = textureAtlasPtr->getSprite("splashcannon");
    cannonRect = canSpritePtr->getBounds();
    canSpritePtr->draw(win, (buttonPtrs.at(1)->left + 16) - cannonRect.width / 2,
                        (buttonPtrs.at(1)->top + 16) - cannonRect.height / 2, 0);
    canSpritePtr->setScale(1.5f, 1.5f);

    // Ice cannon
    canSpritePtr = textureAtlasPtr->getSprite("icecannon");
    cannonRect = canSpritePtr->getBounds();
    canSpritePtr->draw(win, (buttonPtrs.at(2)->left + 16) - cannonRect.width / 2,
                        (buttonPtrs.at(2)->top + 16) - cannonRect.height / 2, 0);
    canSpritePtr->setScale(1.5f, 1.5f);
    }

    // Cursor cannon
    if (canName != "") {
        GameSprite* cursorCanSpritePtr = textureAtlasPtr->getSprite(canName);
        cannonRect = cursorCanSpritePtr->getBounds();
        cursorCanSpritePtr->setScale(1.0f, 1.0f);
        cursorCanSpritePtr->draw(win, (cursorX + 16) - cannonRect.width / 2,
                        (cursorY + 16) - cannonRect.height / 2, 0);
    }
}

const int PurchasePanel::getButtonId(const int& touchX, const int& touchY) {
    for (unsigned int index = 0; index < 3; ++index) {
        if (buttonPtrs.at(index)->contains(touchX, touchY)) {
            return index;
        }
    }

    return -1;
}


PurchasePanel::~PurchasePanel() {

}
