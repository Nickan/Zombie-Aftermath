#include "GameScreenRenderer.h"

GameScreenRenderer::GameScreenRenderer(GameScreenUpdate* ptr) {
    updatePtr = ptr;
    Image image;
    image.loadFromFile("assets/allgameimages.png");

    Texture texture;
    texture.setSmooth(true);

    texture.loadFromImage(image, IntRect(0, 0, 128, 32));

    tiledMapPtr = new TiledMap(texture, TileInfo::tileMapInfo, 4, 32, 32, 38, 50, 800, 600);

    vector<vector<float> > tileInfo = tiledMapPtr->tileInfo;
    /*
    // For debugging...
    for (unsigned int col = 0; col < tileInfo.size(); ++col) {
        for (unsigned int row = 0; row < tileInfo.at(0).size(); ++row) {
            cout << tileInfo.at(col).at(row) << ", ";
        }
        cout << endl;
    }
    */

    textureAtlasPtr = new TextureAtlas("assets/images.png", "assets/images.xml");
    purchasePanPtr = new PurchasePanel(textureAtlasPtr);
    hudPtr = new HeadsUpDisplay(textureAtlasPtr);
    hudPtr->setMiniMapViewRect(updatePtr->mapPos.x, updatePtr->mapPos.y);

    // Normal zombie animation
    texture.loadFromImage(image, IntRect(0, 192, 480, 32));
    aniZomPtr = new Animation(texture, 32, 32, 15, 15, 1, Animation::LOOP);

    // Frozen zombie animation
    texture.loadFromImage(image, IntRect(0, 224, 480, 32));
    aniFrozenZomPtr = new Animation(texture, 32, 32, 15, 15, 1, Animation::LOOP);

    // Normal explosion animation
    texture.loadFromImage(image, IntRect(352, 0, 96, 32));
    aniNorCanExplosionPtr = new Animation(texture, 32, 32, 3, 3, 0.3f, Animation::LOOP);

    // Splash explosion animation
    texture.loadFromImage(image, IntRect(0, 64, 448, 64));
    aniSplCanExplosionPtr = new Animation(texture, 64, 64, 7, 7, 0.5f, Animation::LOOP);

    // Ice explosion animation
    texture.loadFromImage(image, IntRect(0, 128, 448, 64));
    aniIceCanExplosionPtr = new Animation(texture, 64, 64, 7, 7, 0.5f, Animation::LOOP);

    lifeSize.x = 32;
    lifeSize.y = 6;
    lifeIndicator.setFillColor(Color::Yellow);
    lifeIndicator.setSize(lifeSize);

    hasBgImage = false;

    fullBgImage.create(1600, 1200, Color::White);
}


void GameScreenRenderer::render(RenderWindow& win, const float& delta) {
    win.clear(Color::Black);
    Vector2f& mapPos = updatePtr->mapPos;
    tiledMapPtr->draw(win, mapPos.x, mapPos.y);

    // Get a background image of full map
    if (!hasBgImage) {
        hasBgImage = true;
        captureBackground(win);
    }

    drawNormalCannons(win, updatePtr->getNorCanPtrs());
    drawIceCannons(win, updatePtr->getIceCanPtrs());
    drawSplashCannons(win, updatePtr->getSplCanPtrs());

    drawZombies(win);

    // HUD
    hudPtr->draw(win);
    hudPtr->drawMinimap(win, updatePtr->getZombiePtrs(), updatePtr->getNorCanPtrs(),
        updatePtr->getSplCanPtrs(), updatePtr->getIceCanPtrs());

    if (updatePtr->isGameOver()) {
        hudPtr->drawGameOver(win);
    } else {
        hudPtr->drawZomSpawnManager(win, updatePtr->zomSpawnManagerPtr);
    }

    // Purchase panel
    purchasePanPtr->draw(win, 32 * 14, 32 * 14);

    drawBulletExplosions(win);
}

void GameScreenRenderer::drawZombies(RenderWindow& win) {
    Vector2f& mapPos = updatePtr->mapPos;
    // Drawing the zombies
    vector<Zombie*> zomPtrs = updatePtr->getZombiePtrs();
    for (unsigned int index = 0; index < zomPtrs.size(); ++index) {
        Zombie* zomPtr = zomPtrs.at(index);

        float zomX = zomPtr->boundPtr->left + mapPos.x;
        float zomY = zomPtr->boundPtr->top + mapPos.y;
        if (zomPtr->isFrozen()) {
            aniFrozenZomPtr->draw(win, zomX, zomY, zomPtr->rotation, zomPtr->stateTime);
        } else {
            aniZomPtr->draw(win, zomX, zomY, zomPtr->rotation, zomPtr->stateTime);
        }
    }

    // Drawing there life bars. I needed to separate it, as it should not be overdrawn by zombies
    for (unsigned int index = 0; index < zomPtrs.size(); ++index) {
        Zombie* zomPtr = zomPtrs.at(index);
        float zomX = zomPtr->boundPtr->left + mapPos.x;
        float zomY = zomPtr->boundPtr->top + mapPos.y;

        // Setting up the zombie's life indicator
        float lifePercentage = zomPtr->getLife() / zomPtr->getFullLife();
        lifeSize.x = lifePercentage * 32;
        lifeIndicator.setSize(lifeSize);
        lifeIndicator.setPosition(zomX, zomY - 8);
        win.draw(lifeIndicator);
    }
}

void GameScreenRenderer::drawNormalCannons(RenderWindow& win, const vector<Cannon*>& canPtrs) {
    Vector2f& mapPos = updatePtr->mapPos;
    GameSprite* canSprite = textureAtlasPtr->getSprite("normalcannon");
    GameSprite* bulletSprite = textureAtlasPtr->getSprite("normalbullet");

    for (unsigned int index = 0; index < canPtrs.size(); ++index) {
        Cannon* canPtr = canPtrs.at(index);
        FloatRect* boundPtr = canPtr->boundPtr;
        const IntRect& spriteBound = canSprite->getBounds();

        canSprite->setScale(1.0f, 1.0f);
        canSprite->draw(win, (boundPtr->left + boundPtr->width / 2 - spriteBound.width / 2) + mapPos.x,
                                (boundPtr->top + boundPtr->height / 2 - spriteBound.height / 2) + mapPos.y, canPtr->rotation);

        const vector<Bullet*> bulletPtrs = canPtr->getBullets();

        for (unsigned int bulIndex = 0; bulIndex < bulletPtrs.size(); ++bulIndex) {
            Bullet* bulPtr = bulletPtrs.at(bulIndex);
            const IntRect& rect = bulletSprite->getBounds();
            boundPtr = bulPtr->boundPtr;
            if (bulPtr->isFired()) {
                bulletSprite->draw(win, (boundPtr->left + (boundPtr->width / 2)) - (rect.width / 2) + mapPos.x,
                                    (boundPtr->top + (boundPtr->height / 2)) - (rect.height / 2) + mapPos.y, bulPtr->rotation);
            }
        }

    }
}


void GameScreenRenderer::drawIceCannons(RenderWindow& win, const vector<IceCannon*>& canPtrs) {
    Vector2f& mapPos = updatePtr->mapPos;
    GameSprite* canSprite = textureAtlasPtr->getSprite("icecannon");
    GameSprite* bulletSprite = textureAtlasPtr->getSprite("icebullet");

    for (unsigned int index = 0; index < canPtrs.size(); ++index) {
        Cannon* canPtr = canPtrs.at(index);
        FloatRect* boundPtr = canPtr->boundPtr;
        const IntRect& spriteBound = canSprite->getBounds();

        canSprite->setScale(1.0f, 1.0f);
        canSprite->draw(win, (boundPtr->left + boundPtr->width / 2 - spriteBound.width / 2) + mapPos.x,
                                (boundPtr->top + boundPtr->height / 2 - spriteBound.height / 2) + mapPos.y, canPtr->rotation);

        const vector<Bullet*> bulletPtrs = canPtr->getBullets();

        for (unsigned int bulIndex = 0; bulIndex < bulletPtrs.size(); ++bulIndex) {
            Bullet* bulPtr = bulletPtrs.at(bulIndex);
            const IntRect& rect = bulletSprite->getBounds();
            boundPtr = bulPtr->boundPtr;
            if (bulPtr->isFired()) {
                bulletSprite->draw(win, (boundPtr->left + (boundPtr->width / 2)) - (rect.width / 2) + mapPos.x,
                                    (boundPtr->top + (boundPtr->height / 2)) - (rect.height / 2) + mapPos.y, bulPtr->rotation);
            }
        }
    }
}

void GameScreenRenderer::drawSplashCannons(RenderWindow& win, const vector<SplashCannon*>& canPtrs) {
    Vector2f& mapPos = updatePtr->mapPos;
    GameSprite* canSprite = textureAtlasPtr->getSprite("splashcannon");
    GameSprite* bulletSprite = textureAtlasPtr->getSprite("splashbullet");

    for (unsigned int index = 0; index < canPtrs.size(); ++index) {
        Cannon* canPtr = canPtrs.at(index);
        FloatRect* boundPtr = canPtr->boundPtr;
        const IntRect& spriteBound = canSprite->getBounds();

        canSprite->setScale(1.0f, 1.0f);
        canSprite->draw(win, (boundPtr->left + boundPtr->width / 2 - spriteBound.width / 2) + mapPos.x,
                                (boundPtr->top + boundPtr->height / 2 - spriteBound.height / 2) + mapPos.y, canPtr->rotation);

        const vector<Bullet*> bulletPtrs = canPtr->getBullets();

        for (unsigned int bulIndex = 0; bulIndex < bulletPtrs.size(); ++bulIndex) {
            Bullet* bulPtr = bulletPtrs.at(bulIndex);
            const IntRect& rect = bulletSprite->getBounds();
            boundPtr = bulPtr->boundPtr;
            if (bulPtr->isFired()) {
                bulletSprite->draw(win, (boundPtr->left + (boundPtr->width / 2)) - (rect.width / 2) + mapPos.x,
                                    (boundPtr->top + (boundPtr->height / 2)) - (rect.height / 2) + mapPos.y, bulPtr->rotation);
            }
        }
    }
}


void GameScreenRenderer::drawBulletExplosions(RenderWindow& win) {
    vector<AnimationExplosionTimer*> timerPtrs = updatePtr->aniExpTimerPtrs;
    Vector2f& mapPos = updatePtr->mapPos;

    for (unsigned int index = 0; index < timerPtrs.size(); ++index) {
        AnimationExplosionTimer* timer = timerPtrs.at(index);

        float centerX;
        float centerY;
        if (timer->type == ExplosionType::NORMAL) {
            centerX = (timer->x + mapPos.x) - (aniNorCanExplosionPtr->getWidth() / 2);
            centerY = (timer->y + mapPos.y) - (aniNorCanExplosionPtr->getHeight() / 2);

            aniNorCanExplosionPtr->draw(win, centerX, centerY, 0, 0.3f - timer->stateTime);
        } else if (timer->type == ExplosionType::SPLASH) {
            centerX = (timer->x + mapPos.x) - (aniSplCanExplosionPtr->getWidth() / 2);
            centerY = (timer->y + mapPos.y) - (aniSplCanExplosionPtr->getHeight() / 2);

            aniSplCanExplosionPtr->draw(win, centerX, centerY, 0, 0.5f - timer->stateTime);
        } else {
            centerX = (timer->x + mapPos.x) - (aniIceCanExplosionPtr->getWidth() / 2);
            centerY = (timer->y + mapPos.y) - (aniIceCanExplosionPtr->getHeight() / 2);

            aniIceCanExplosionPtr->draw(win, centerX, centerY, 0, 0.5f - timer->stateTime);
        }
    }
}

const vector<vector<float> >& GameScreenRenderer::getTileMapInfo() {
    return tiledMapPtr->tileInfo;
}

void GameScreenRenderer::captureBackground(RenderWindow& win) {
    // Upper left image
    Image upperLeftImage = win.capture();
    fullBgImage.copy(upperLeftImage, 0, 0, IntRect(0, 0, 800, 600), true);

    // Upper right image
    tiledMapPtr->draw(win, -800, 0);
    Image upperRightImage = win.capture();
    fullBgImage.copy(upperRightImage, 800, 0, IntRect(0, 0, 800, 600), true);

    // Lower left image
    tiledMapPtr->draw(win, 0, -600);
    Image lowerLeftImage = win.capture();
    fullBgImage.copy(lowerLeftImage, 0, 600, IntRect(0, 0, 800, 600), true);

    // Lower right image
    tiledMapPtr->draw(win, -800, -600);
    Image lowerRightImage = win.capture();
    fullBgImage.copy(lowerRightImage, 800, 600, IntRect(0, 0, 800, 600), true);

    hudPtr->setMiniMapBgImage(fullBgImage);

    //...
    cout << "Size: " << fullBgImage.getSize().x << ": " << fullBgImage.getSize().y << endl;
}

GameScreenRenderer::~GameScreenRenderer() {
    delete aniFrozenZomPtr;
    delete aniZomPtr;
    delete hudPtr;
    delete purchasePanPtr;
    delete textureAtlasPtr;
    delete tiledMapPtr;
}
