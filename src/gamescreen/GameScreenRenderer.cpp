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
    tempSpritePtr = textureAtlasPtr->getSprite("normalcannon");

    texture.loadFromImage(image, IntRect(224, 32, 32, 32));
}


void GameScreenRenderer::render(RenderWindow& win, const float& delta) {
    tiledMapPtr->draw(win, updatePtr->mapPos.x, updatePtr->mapPos.y);

    tempSpritePtr->draw(win, 32, 32, 0);
}

GameScreenRenderer::~GameScreenRenderer() {
    delete tiledMapPtr;
}
