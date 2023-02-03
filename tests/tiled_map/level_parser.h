#ifndef _LEVEL_PARSER_H_
#define _LEVEL_PARSER_H_

#include "tinyxml.h"
#include "tile_layer.h"
#include <string>

class LevelParser {
public:
    Level *parseLevel(const char *levelFile);

private:
    void parseEmbedTilesets(TiXmlElement *pTilesetRoot, std::vector<Tileset> *pTilesets);
    void parseTileLayer(TiXmlElement *pTileElement, std::vector<Layer *> *pLayers, const std::vector<Tileset> *pTilesets);
    void parseOutsideTilesets(const char *tilesetFile, TiXmlElement *pTileset, std::vector<Tileset> *pTilesets);
    std::string getLevelDir() const {
        return m_levelDir;
    }
    std::string extractLevelDir(const char *levelFile);

    int m_tileSize;
    int m_width;
    int m_height;
    std::string m_tiledVersion;

    std::string m_levelDir;
};

#endif /* _LEVEL_PARSER_H_ */
