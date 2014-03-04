#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics/Rect.hpp>
#include <string>


using namespace sf;
using namespace std;

// Just needed for the TiledMap class, as making a lot of GameSprite is not resource wise.

class Cell : public FloatRect {
    public:
        Cell();
        Cell(const float& left, const float& top, const float& width, const float& height, const float rotation);

        string name;
        float rotation;
        virtual ~Cell();
    protected:
    private:
};

#endif // CELL_H
