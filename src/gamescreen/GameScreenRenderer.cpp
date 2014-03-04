#include "GameScreenRenderer.h"

GameScreenRenderer::GameScreenRenderer(GameScreenUpdate* ptr) {
    Image image;
    image.loadFromFile("assets/allgameimages.png");

    Texture texture;
    texture.setSmooth(true);

    texture.loadFromImage(image, IntRect(0, 0, 128, 32));

    unsigned int width = 32;
    unsigned int height = 32;
    unsigned int rows = 10;
    unsigned int columns = 10;
    unsigned int screenWidth = 800;
    unsigned int screenHeight = 600;
    tiledMapPtr = new TiledMap(texture, TileInfo::tileMapInfo, 4, width, height, rows, columns, screenWidth, screenHeight);

    vector<vector<float> > tileInfo = tiledMapPtr->tileInfo;

    // For debugging...
    for (unsigned int col = 0; col < tileInfo.size(); ++col) {
        for (unsigned int row = 0; row < tileInfo.at(0).size(); ++row) {
            cout << tileInfo.at(col).at(row) << ", ";
        }
        cout << endl;
    }


    TextureAtlas* textureAtlasPtr = new TextureAtlas("assets/images.png", "assets/images.xml");
    tempSpritePtr = textureAtlasPtr->getSprite("normalcannon");

    texture.loadFromImage(image, IntRect(224, 32, 32, 32));
}


void GameScreenRenderer::render(RenderWindow& win, const float& delta) {
    tiledMapPtr->draw(win);

    tempSpritePtr->draw(win);
}

GameScreenRenderer::~GameScreenRenderer() {
    delete tiledMapPtr;
}
