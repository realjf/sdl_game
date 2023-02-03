#ifndef _LEVEL_PARSER_H_
#define _LEVEL_PARSER_H_

#include "tinyxml.h"
#include "tile_layer.h"
#include <string>

class LevelParser {
public:
    Level *parseLevel(const char *levelFile);

private:
    void parseTilesets(TiXmlElement *pTilesetRoot, std::vector<Tileset> *pTilesets);
    void parseTileLayer(TiXmlElement *pTileElement, std::vector<Layer *> *pLayers, const std::vector<Tileset> *pTilesets);
    std::string getLevelDir() const {
        return m_levelDir;
    }

    int m_tileSize;
    int m_width;
    int m_height;

    std::string m_levelDir;
};

#endif /* _LEVEL_PARSER_H_ */
