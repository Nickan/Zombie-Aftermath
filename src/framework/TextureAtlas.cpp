#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(const Texture& texture, const string& filePath)
:texture(texture) {

}

TextureAtlas::TextureAtlas(const string& texturePath, const string& filePath) {
    ifstream atlasFile(filePath.c_str());
    if (!atlasFile) {
        cout << "Error loading: " << filePath << endl;
        return;
    }

    readFile(atlasFile, cellsPtrList);

    // Reading the values of the cellsList...
    for (unsigned int index = 0; index < cellsPtrList.size(); ++ index) {
        Cell* cell = cellsPtrList.at(index);
        cout << "cell: " << index << ": " << cell->left << ", " << cell->top << ", " << cell->width << ", " << cell->height << endl;
    }

    createGameSprite(cellsPtrList, texturePath);
}

void TextureAtlas::readFile(ifstream& atlasFile, vector<Cell*>& cellsList) {
    if (atlasFile.is_open()) {
        string str;

        bool firstTime = true;
        while (atlasFile >> str) {
            size_t quotationIndex = str.find('"');

            // There is existing quotation in the str
            if (quotationIndex != -1) {

                // If that is the first str that has quotation, reanalyze and ignore it
                if (firstTime) {
                    firstTime = false;
                    continue;
                }

                // Trim off the unnecessary characters from the string, including the quotation mark
                setNeededString(str, quotationIndex);

                // Create a new cell, set its name
                Cell* cellPtr = new Cell();
                cellsList.push_back(cellPtr);
                cellPtr->name = str;

                setCellInfo(atlasFile, cellPtr);
            }
        }
    }
}

void TextureAtlas::setNeededString(string& str, unsigned int startingIndex) {
    // Delete the beginning char to the index of starting quotation mark
    str.erase(0, startingIndex + 1);

    // Find the ending quotation mark
    size_t endingIndex = str.find('"');

    // Delete from the ending quotation mark index to the last letter of the str
    str.erase(endingIndex, str.size() - 1);
}

void TextureAtlas::setCellInfo(ifstream& atlasFile, Cell* cellPtr) {
    string str;
    int loopCount = 0;
    int loopLimit = 4;
    // The next four str that has quotation will be the left, top, width and the height of the cell
    while (atlasFile >> str) {
        size_t quotationIndex = str.find('"');

        // If the starting quotation mark has been found
        if (quotationIndex != -1) {
            setNeededString(str, quotationIndex);
            float value = atoi(str.c_str());
            switch (loopCount) {
            case 0: cellPtr->left = value;
                cout << "value: " << value << endl;
                break;
            case 1: cellPtr->top = value;
                break;
            case 2: cellPtr->width = value;
                break;
            case 3: cellPtr->height = value;
                break;
            default:
                break;
            }
        //...
        //    cout << "value: " << value << endl;
        }

        ++loopCount;
        if (loopCount >= loopLimit) {
        //...
        //    for (unsigned int index = 0; index < textureList.size(); ++index) {
        //        cout << textureList.at(index) << ", ";
        //    }
        //    cout << endl;
            break;
        }

    }
}

void TextureAtlas::createGameSprite(vector<Cell*>& cellsPtrList, const string& texturePath) {
    Image image;
    image.loadFromFile(texturePath.c_str());
    texture.setSmooth(true);

    for (unsigned int index = 0; index < cellsPtrList.size(); ++index) {
        Cell* cell = cellsPtrList.at(index);
        IntRect rect = IntRect(cell->left, cell->top, cell->width, cell->height);
        texture.loadFromImage(image, rect);
        spriteList.push_back(new GameSprite(texture, 0, 0));
    }
}

GameSprite* TextureAtlas::getSprite(const string& name) {
    for (unsigned int index = 0; index < cellsPtrList.size(); ++index) {
        Cell* cell = cellsPtrList.at(index);
        if (cell->name == name) {
            return spriteList.at(index);
        }
    }
    return NULL;
}

TextureAtlas::~TextureAtlas() {
    for (unsigned int index = 0; index < cellsPtrList.size(); ++ index) {
        delete cellsPtrList.at(index);
    }
}
