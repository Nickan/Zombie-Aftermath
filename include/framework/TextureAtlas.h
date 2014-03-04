#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include <SFML/Graphics/Texture.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Cell.h"
#include "GameSprite.h"

using namespace sf;
using namespace std;
// My attempt to make a texture atlas to ease management of textures

class TextureAtlas
{
    public:
        TextureAtlas(const string& texturePath, const string& filePath);

        GameSprite* getSprite(const string& name);
        virtual ~TextureAtlas();
    protected:
    private:
        // will trim off the unnecessary characters
        void setNeededString(string& str, unsigned int startingIndex);
        void readFile(ifstream& atlasFile, vector<Cell*>& cellsList);

        void setCellInfo(ifstream& atlasFile, Cell* cellPtr);
        void createGameSprite(vector<Cell*>& cellsPtrList, const string& texturePath);

        // The value for each cell is not saved when I am not using pointer for the cell
        vector<Cell*> cellsPtrList;
        vector<GameSprite*> spritesPtrList;
};

#endif // TEXTUREATLAS_H
