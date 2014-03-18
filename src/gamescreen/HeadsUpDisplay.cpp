#include "HeadsUpDisplay.h"

HeadsUpDisplay::HeadsUpDisplay(TextureAtlas* textureAtlasPtr):
textureAtlasPtr(textureAtlasPtr) {
    gameTextPtr = new GameText("assets/sansation.ttf");
    gameTextPtr->setCharSize(12);

    restartColor.g = 255;
    restartColor.a = 50;
    menuColor.b = 255;
    menuColor.a = 50;
    bgRect.setFillColor(restartColor);
    bgRect.setSize(Vector2f(64, 32));

    restartRect = IntRect(32 * 10, 32 * 10, 64, 32);
    menuRect = IntRect( (32 * 12) + 10, 32 * 10, 64, 32);

    miniMapPtr =  new MiniMap();
}


void HeadsUpDisplay::draw(RenderWindow& win) {
    GameSprite* panelPtr = textureAtlasPtr->getSprite("toppanel");

    // Top panel
    for (unsigned int index = 0; index < 25; ++index) {
        panelPtr->draw(win, 32 * index, 0, 0);
    }

    // Bottom panel
    for (unsigned int index = 0; index < 18; ++index) {
        panelPtr->draw(win, (32 * index) + (32 * 7), 32 * 14, 180);
    }

    // Clear panel
    panelPtr = textureAtlasPtr->getSprite("panelclear");
    for (unsigned int y = 0; y < 18; ++y) {
        for (unsigned int x = 0; x < 5; ++x) {
            panelPtr->draw(win, (32 * y) + (32 * 7), (32 * 15) + (32 * x), 0);
        }
    }

    GameSprite* bagMoneyPtr = textureAtlasPtr->getSprite("bagmoney");
    bagMoneyPtr->setScale(0.7f, 0.7f);
    bagMoneyPtr->draw(win, 4 * 32, 0, 0);
    textureAtlasPtr->getSprite("heart")->draw(win, 12 * 32, 4, 0);
    textureAtlasPtr->getSprite("skull")->draw(win, 20 * 32, 0, 0);

    // Screen texts
    gameTextPtr->setCharSize(12);
    gameTextPtr->draw(win, ToString::getString(Settings::cash), (4 * 32) + 20, 2, Color::White);
    gameTextPtr->draw(win, ToString::getString(Settings::life), (12 * 32) + 20, 2, Color::White);
    gameTextPtr->draw(win, ToString::getString(Settings::score), (20 * 32) + 20, 2, Color::White);
}

void HeadsUpDisplay::drawGameOver(RenderWindow& win) {
    // For the restart rect
    bgRect.setPosition(restartRect.left, restartRect.top);
    bgRect.setFillColor(restartColor);
    win.draw(bgRect);

    // For the menu rect
    bgRect.setPosition(menuRect.left, menuRect.top);
    bgRect.setFillColor(menuColor);
    win.draw(bgRect);

    gameTextPtr->setCharSize(24);
    gameTextPtr->draw(win, "Game Over!!!", (10 * 32), 9 * 32, Color::White);

    gameTextPtr->setCharSize(12);
    gameTextPtr->draw(win, "Restart", restartRect.left + 12, restartRect.top + 6, Color::White);
    gameTextPtr->draw(win, "Exit", menuRect.left + 22, menuRect.top + 6, Color::White);
}

void HeadsUpDisplay::drawMinimap(RenderWindow& win, const vector<Zombie*> zomPtrs, const vector<Cannon*> norCanPtrs,
        const vector<SplashCannon*> splCanPtrs, const vector<IceCannon*> iceCanPtrs) {
    miniMapPtr->draw(win, zomPtrs, norCanPtrs, splCanPtrs, iceCanPtrs);
}


void HeadsUpDisplay::setMiniMapBgImage(const Image& image) {
    miniMapPtr->setImage(image);
}


void HeadsUpDisplay::setRestartButtonOpaque(const bool& opaque) {
    if (opaque) {
        restartColor.a = 255;
    } else {
        restartColor.a = 50;
    }
}

void HeadsUpDisplay::setMenuButtonOpaque(const bool& opaque) {
    if (opaque) {
        menuColor.a = 255;
    } else {
        menuColor.a = 50;
    }
}

void HeadsUpDisplay::setMiniMapViewRect(const float& x, const float& y) {
    miniMapPtr->setViewRectPos(x, y);
}


const bool HeadsUpDisplay::isOverRestartButton(const int& x, const int& y) {
    return restartRect.contains(x, y);
}

const bool HeadsUpDisplay::isOverMenuButton(const int& x, const int& y) {
    return menuRect.contains(x, y);
}

HeadsUpDisplay::~HeadsUpDisplay() {
    delete gameTextPtr;
    delete miniMapPtr;
}
