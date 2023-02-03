#ifndef _LEVEL_PARSER_H_
#define _LEVEL_PARSER_H_

#include "tinyxml.h"
#include "level.h"

class LevelParser {
public:
    Level *parseLevel(const char *levelFile);

private:
    void parseTilesets(TiXmlElement *pTilesetRoot, std::vector<Tileset> *pTilesets);
    void parseTileLayer(TiXmlElement *pTileElement, std::vector<Layer *> *pLayers, const std::vector<Tileset> *pTilesets);

    int m_tileSize;
    int m_width;
    int m_height;
};

#endif /* _LEVEL_PARSER_H_ */
