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

    TextureAtlas* textureAtlasPtr = new TextureAtlas("assets/images.png", "assets/images.xml");
    norCanSpritePtr = textureAtlasPtr->getSprite("normalcannon");
    norCanBulSpritePtr = textureAtlasPtr->getSprite("normalbullet");

    texture.loadFromImage(image, IntRect(0, 192, 480, 32));

    aniZomPtr = new Animation(texture, 32, 32, 15, 15, 1, Animation::LOOP);

    lifeIndicator.setFillColor(Color::Yellow);
    lifeIndicator.setSize(Vector2f(32, 8));
}


void GameScreenRenderer::render(RenderWindow& win, const float& delta) {
    tiledMapPtr->draw(win, updatePtr->mapPos.x, updatePtr->mapPos.y);

    vector<Zombie*> zomPtrs = updatePtr->getZombiePtrs();
    for (unsigned int index = 0; index < zomPtrs.size(); ++index) {
        Zombie* zomPtr = zomPtrs.at(index);

        aniZomPtr->draw(win, zomPtr->boundPtr->left, zomPtr->boundPtr->top, zomPtr->rotation, zomPtr->stateTime);
    }

    vector<Cannon*> norCanPtrs = updatePtr->getNorCanPtrs();
    for (unsigned int index = 0; index < norCanPtrs.size(); ++index) {
        Cannon* norCanPtr = norCanPtrs.at(index);
        FloatRect* boundPtr = norCanPtr->boundPtr;
        const IntRect& spriteBound = norCanSpritePtr->getBounds();

        norCanSpritePtr->draw(win, boundPtr->left + boundPtr->width / 2 - spriteBound.width / 2,
                                boundPtr->top + boundPtr->height / 2 - spriteBound.height / 2, norCanPtr->rotation);

        const vector<Bullet*> bulletPtrs = norCanPtr->getBullets();

        for (unsigned int bulIndex = 0; bulIndex < bulletPtrs.size(); ++bulIndex) {
            Bullet* bulPtr = bulletPtrs.at(bulIndex);
            if (bulPtr->updating) {
                const IntRect& sprBound = norCanBulSpritePtr->getBounds();
                norCanBulSpritePtr->draw(win, bulPtr->boundPtr->left - (sprBound.width / 2),
                                            bulPtr->boundPtr->top - (sprBound.height / 2), bulPtr->rotation);
            }
        }
    }
}

GameScreenRenderer::~GameScreenRenderer() {
    delete tiledMapPtr;
}
