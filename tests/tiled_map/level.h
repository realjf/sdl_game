#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <string>
#include <vector>
#include "layer.h"

struct Tileset {
    int firstGridID;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int width;
    int height;
    int numColumns;
    int count;
    std::string name;
};

class LevelParser;

class Level {
public:
    ~Level() {}

    void update();
    void render();

    std::vector<Tileset> *getTilesets() {
        return &m_tilesets;
    }

    std::vector<Layer *> *getLayers() {
        return &m_layers;
    }

private:
    friend class LevelParser;
    Level();

private:
    std::vector<Tileset> m_tilesets;
    std::vector<Layer *> m_layers;
};

#endif /* _LEVEL_H_ */
