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

    texture.loadFromImage(image, IntRect(0, 192, 480, 32));

    aniZomPtr = new Animation(texture, 32, 32, 15, 15, 1, Animation::LOOP);

    lifeIndicator.setFillColor(Color::Yellow);
    lifeIndicator.setSize(Vector2f(32, 8));
}


void GameScreenRenderer::render(RenderWindow& win, const float& delta) {
    Vector2f& mapPos = updatePtr->mapPos;
    tiledMapPtr->draw(win, mapPos.x, mapPos.y);

    // Drawing the zombies
    vector<Zombie*> zomPtrs = updatePtr->getZombiePtrs();
    for (unsigned int index = 0; index < zomPtrs.size(); ++index) {
        Zombie* zomPtr = zomPtrs.at(index);

        aniZomPtr->draw(win, zomPtr->boundPtr->left + mapPos.x, zomPtr->boundPtr->top + mapPos.y,
        zomPtr->rotation, zomPtr->stateTime);
    }

    drawNormalCannons(win, updatePtr->getNorCanPtrs());
    drawIceCannons(win, updatePtr->getIceCanPtrs());
    drawSplashCannons(win, updatePtr->getSplCanPtrs());

    purchasePanPtr->draw(win, 128, 128);
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
                const IntRect& sprBound = bulletSprite->getBounds();
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
                const IntRect& sprBound = bulletSprite->getBounds();
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
                const IntRect& sprBound = bulletSprite->getBounds();
                bulletSprite->draw(win, (boundPtr->left + (boundPtr->width / 2)) - (rect.width / 2) + mapPos.x,
                                    (boundPtr->top + (boundPtr->height / 2)) - (rect.height / 2) + mapPos.y, bulPtr->rotation);
            }
        }
    }
}


const vector<vector<float> >& GameScreenRenderer::getTileMapInfo() {
    return tiledMapPtr->tileInfo;
}

GameScreenRenderer::~GameScreenRenderer() {
    delete textureAtlasPtr;
    delete tiledMapPtr;
    delete purchasePanPtr;
}
